# 🌫️ Mist
<img src="./Mist.png" width="300" align="center">

## ❓ What is it?
***Mist* is a simple x86_64 operating system made for learning how the PC works**

## 🛠️ How does it work?
Mist currently has a few essential components:
- Bootloader
  - Paging
  - GDT setup
  - A20 setup
  - Kernel loading to memory

- Kernel
  - PMM
  - Own standard C library
  - VGA driver
  - VMM

- Todo:
  - [ ] IDT
  - [ ] Keyboard driver
  - [ ] Shell
  - [ ] Some utils
  - [ ] etc.

### Explanation...
<details>

#### 🥇 Bootloader

<details>

- **Paging:**
  - Address of PML4: 0x1000
  - Address of PDPT: 0x2000
  - Address of PD: 0x3000
  - __No__ PT: There are 2MB pages

- **GDT:**
  - GDT settings you can see at the end of boot/BootLoader.asm

- **A20:**
  - Same as GDT

- **Kernel load:**
  - Firstly kernel is loaded to the 0x10000 with BIOS interrupts
  - Then it moves to 0x100000 using a loop
  - It calls with:

  ```nasm
  mov rax, 0x100000
  call rax
  ```

</details>

#### 🎯 Kernel

<details>

- **PMM:**

A tool that has a bitmap of all pages and tracks their statuses (1 - already allocated; 0 - free)

Also it have some functions you can use in your kernel-level programs (And it will be used by many of tools that I will make later)

|Function                |What it does                                    |
|:----------------------:|:-----------------------------------------------|
|`pmm_init()`            |Inits the PMM                                   |
|`alloc()`               |Gives addresses of free page with lowest address|
|`pmm_free(addr of page)`|Clear status of given page                      |

- **VMM:**

Virtual Memory Manager. Handles virtual-to-physical address translation and manages page tables dynamically *(until I implement the scheduler)*.

It has:
- `ptt[]` — Array storing physical addresses of all active PML4 root tables
- `pts` — Bitmask tracking which PML4 slots are used (`1`) or free (`0`)

Also it has some functions you can use in your kernel-level programs:

|Function                                          |What it does                                                    |
|:------------------------------------------------:|:---------------------------------------------------------------|
|`vmm_init()`                                      |Initializes VMM, reads kernel PML4 from `CR3`, reserves slot `0`|
|`vmm_create_process()`                            |Creates new PML4 for process, copies kernel mappings, returns ID|
|`vmm_alloc(int id, u64 virt, u64 phys, u64 flags)`|Maps virtual page to physical frame, creates tables if needed   |
|`pt_switch(int ptid)`                             |Switches address space by loading PML4 into `CR3`               |

- **Standard C library:**

Import:
```C
#include <mist.h>
```
Table of functions that it have:
|Name                 |What it does                                                                  |
|:-------------------:|:-----------------------------------------------------------------------------|
|`copy(void* dst, void* src, usize n)`            |Clone n bytes from cd to ab                                                   |
|`copyfb(void* dst, void src, usize n)`           |Same as copy(), but from the back                                             |
|`fill(void* dst, void* src, usize n)`            |Fill ab with c n times                                                        |
|`iseq(const void* a, const void* b, usize n)`    |Check the equality of ab and cd (True - ab==cd; False - ab!=cd)               |
|`clear()`                                        |Clears the screen and moves cursor to left up of screen                       |
|`putchar(char a)`                                |Insert a to the cursor place and move cursor right (Down if screen width ends)|
|`print_str(const char* str)`                     |Just print... You know                                                        |
|`print_hex(u64 i)`                               |Use print_str() and u2s() to print hexadecimal numbers                        |
|`print_dec(u64 i)`                               |Use print_str() and u2s() to print decimal numbers                            |
|`print_bin(u64 i)`                               |Use print_str() and u2s() to print binary numbers                             |
|`print_oct(u64 i)`                               |Use print_str() and u2s() to print octal numbers                              |
|`u2s(u64 val, char* buf, u8 base)`               |Convert number with selected base to string                                   |

- **VGA driver:**

It have couple of functions that using by any functions in standard library

|Name                  |What it does                                    |
|:--------------------:|:-----------------------------------------------|
|`vga_clear()`         |Clears the screen without moving cursor         |
|`vga_putchar(x, y, c)`|Puts c to place that have (x, y) coordinates    |
|`vga_getchar(x, y)`   |Returns character that was on (x, y) coordinates|

**I recommend you use tools from standard library to work with screen instead of using VGA driver functions**

</details>
</details>

##  🏁 Get started
***I DON'T recommend to try Mist on real PC. Instead of this use QEMU***

Also you should have GCC to compile Mist
> **Recommendation** ~~(Again...)~~: Use Linux to this
You can start with 2 ways:

Compile by yourself:
- <details>

  - Clone Mist repo:

  ```
  git clone https://github.com/L-fyz/Mist
  ```
  - Compile (GCC):

  ```
  cd ~/Mist
  make
  ```
  - Run with QEMU:

  ```
  make run
  ```

</details>

Use already compiled Mist.img from releases:
- <details>

  - Copy Mist.img:
  ```
  wget https://github.com/L-fyz/Mist/releases/download/v0.2/Mist.img ~/Mist
  ```
  - Run with QEMU:
  ```
  qemu-system-x86_64 -drive format=raw,file=Mist.img -no-reboot
  ```

</details>

## 😰 Issues
***Mist - young project made by schoolboy***

It may contain bugs and errors

If you have one of these, you can visit the [issues](https://github.com/L-fyz/Mist/issues)
Also you can do pull requests with your code. You're welcome!
