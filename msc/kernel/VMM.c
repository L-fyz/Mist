#include "mist.h"

static u64 ptt[64] __attribute__((section(".data")));
static u64 pts;

bool vmm_init(void) {
    u64 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    if (!(cr0 & (1ULL << 31))) {
        return false;
    }

    u64 start_pml4;
    __asm__ volatile("mov %%cr3, %0" : "=r"(start_pml4));

    if (start_pml4 & 0xFFF) {
        return false;
    }
    if (start_pml4 < 0x1000) {
        return false;
    }
    if (start_pml4 >= 0xA0000 && start_pml4 <= 0xFFFFF) {
        return false;
    }

    pts = 0;
    for (int i = 0; i < 64; i++) {
        ptt[i] = 0;
    }

    ptt[0] = start_pml4;
    pts |= (1ULL << 0);

    return true;
}

int vmm_create_process(void) {
    for (int id = 1; id < 64; id++) {
        if (!(pts & (1ULL << id))) {
            pts |= (1ULL << id);

            u64 pml4_phys = alloc();
            if (!pml4_phys) return -1;

            u64* pml4_virt = (u64*)pml4_phys;
            u64* kern_pml4 = (u64*)ptt[0];

            for (int i = 0; i < 512; i++) {
                pml4_virt[i] = kern_pml4[i];
            }

            ptt[id] = pml4_phys;
            return id;
        }
    }
    return -1;
}

void vmm_alloc(int id, u64 virt, u64 phys, u64 flags) {
    u64* pml4 = (u64*)ptt[id];
    u32 pml4_idx = (virt >> 39) & 0x1FF;
    u32 pdpt_idx = (virt >> 30) & 0x1FF;
    u32 pd_idx   = (virt >> 21) & 0x1FF;

    if (!(pml4[pml4_idx] & present)) {
        u64 pdpt_phys = alloc();
        if (!pdpt_phys) return;
        u64* pdpt_virt = (u64*)pdpt_phys;
        for (int i = 0; i < 512; i++) pdpt_virt[i] = 0;
        pml4[pml4_idx] = pdpt_phys | present | write;
    }
    u64* pdpt = (u64*)(pml4[pml4_idx] & (~0xFFFULL));

    if (!(pdpt[pdpt_idx] & present)) {
        u64 pd_phys = alloc();
        if (!pd_phys) return;
        u64* pd_virt = (u64*)pd_phys;
        for (int i = 0; i < 512; i++) pd_virt[i] = 0;
        pdpt[pdpt_idx] = pd_phys | present | write;
    }
    u64* pd = (u64*)(pdpt[pdpt_idx] & (~0xFFFULL));

    pd[pd_idx] = (phys & (~0x1FFFFFULL)) | flags | PS;

    __asm__ volatile("invlpg (%0)" :: "r"(virt) : "memory");
}

void pt_switch(int ptid) {
    __asm__ volatile("mov %0, %%cr3" : : "r"(ptt[ptid]) : "memory");
}
