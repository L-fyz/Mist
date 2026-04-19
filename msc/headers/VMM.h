#pragma once
#include "types.h"

#define present (1ULL << 0)
#define write (1ULL << 1)
#define user (1ULL << 2)
#define PS (1ULL << 7)

bool vmm_init(void);
int vmm_create_process(void);
void pt_switch(int ptid);
void vmm_alloc(int ptid, u64 virt, u64 phys, u64 flags);
