# Kernel
I don't know waht to say here. This is Mist's kernel

## Tools
Now here is:
- PMM
- VMM
- IDT

### PMM
They are in PMM.c:

|Name                                         |What it does                                                                  |
|:-------------------------------------------:|:-----------------------------------------------------------------------------|
|`pmm_init()`                                 |Inits the PMM                                                                 |
|`alloc()`                                    |Gives addresses of free page with lowest address                              |
|`pmm_free(addr of page)`                     |Clear status of given page                                                    |

## VMM
They are in VMM.c:

|Name                                              |What it does                                                    |
|:------------------------------------------------:|:---------------------------------------------------------------|
|`vmm_init()`                                      |Initializes VMM, reads kernel PML4 from `CR3`, reserves slot `0`|
|`vmm_create_process()`                            |Creates new PML4 for process, copies kernel mappings, returns ID|
|`vmm_alloc(int id, u64 virt, u64 phys, u64 flags)`|Maps virtual page to physical frame, creates tables if needed   |
|`pt_switch(int ptid)`                             |Switches address space by loading PML4 into `CR3`               |

## IDT
They are in IDT.c:

|Name                                                     |What it does                         |
|:-------------------------------------------------------:|:------------------------------------|
|`idt_init(void)`                                         |Initializes IDT                      |
|`isr_handler(u8 vector, u64 error_code)`                 |Handles interrupts with given vector |
|`idt_set_gate(u8 vector, void* handler, u8 type, u8 dpl)`|Setup hendler with standard type     |
|Entire `isr_stub.asm`                                    |Just makes stub for every isr        |
