# 🌫️ Mist
![Logo](./Mist.png)

## ❓ What is it?
***Mist* is a simple x86_64 operating system made for learning how the PC works**

## 🛠️ How does it works?
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

- Todo:
  - [ ] VMM
  - [ ] IDT
  - [ ] Keyboard driver
  - [ ] Shell
  - [ ] Some utils
  - [ ] etc.

### Explanation...
#### 🥇 Bootloader
- **Paging**:
  - Address of PML4: 0x1000
  - Address of PDPT: 0x2000
  - Address of PD: 0x3000
  - __No__ PT: There are 2MB pages

- **GDT**:
  - GDT settings you can see at the end of boot/BootLoader.asm

- **A20**:
  - Same as GDT

- **Kernel load**:
  - Firstly kernel is loaded to the 0x10000 with BIOS interrupts
  - Then it moves to 0x100000 using a loop
  - It calls with:
  ```nasm
  mov rax, 0x100000
  call rax
  ```
#### 🎯 Kernel
1. PMM:
A tool that has a bitmap of all pages and tracks their statuses (1 - already allocated; 0 - free)
Also it have some functions you can use in your kernel-level programs (And it will be used by many of tools that I will make later)

|Function                |What it does                                    |
|:----------------------:|:----------------------------------------------:|
|`alloc()`               |Gives addresses of free page with lowest address|
|`pmm_free(addr of page)`|Clear status of given page                      |

2. Standard C library:
Import:
```C
#include <mist.h>
```
Table of functions that it have:
|Name               |What it does                                                                  |
|:-----------------:|:-----------------------------------------------------------------------------|
|`copy(ab, cd, n)`  |Clone n bytes from cd to ab                                                   |
|`copyfb(ab, cd, n)`|Same as clone() but from the back                                             |
|`fill(ab, c, n)`   |Fill ab with c n times                                                        |
|`iseq(ab, cd, n)`  |Check the equality of ab and cd (True - ab==cd; False - ab!=cd)               |
|`clear()`          |Clears the screen and moves cursor to left up of screen                       |
|`putchar(a)`       |Insert a to the cursor place and move cursor right (Down if screen width ends)|
|`print(str)`       |Just print... You know                                                        |

3. VGA driver
It have couple of functions that using by any functions in standard library

|Name                  |What it does                                    |
|:--------------------:|:----------------------------------------------:|
|`vga_clear()`         |Clears the screen without moving cursor         |
|`vga_putchar(x, y, c)`|Puts c to place that have (x, y) coordinates    |
|`vga_getchar(x, y)`   |Returns character that was on (x, y) coordinates|
**I recommend you use tools from standard library to work with screen instead of using VGA driver functions**

##  🏁 Get started
***I DON'T recommend to try Mist on real PC. Instead of this use QEMU***
Also you should have GCC to compile Mist
> **Recomendation** ~~(Again...)~~: Use Linux to this
You can start with 2 ways:

- Compile by yourself
  -. Clone Mist repo:
  ```
  git clone https://github.com/L-fyz/Mist
  ```
  -. Compile (GCC):
  ```
  cd ~/Mist
  make
  ```
  -. Run with QEMU:
  ```
  make run
  ```

- Use already compiled Mist.img from repo
  - Copy Mist.img:
  ```
  wget https://raw.githubusercontent.com/L-fyz/Mist/main/Mist.img ~/Mist
  ```
  - Run with QEMU:
  ```
  qemu-system-x86_64 -drive format=raw,file=Mist.img -no-reboot
  ```

## 😰 Issues
***Mist - young project made by schoolboy***

It can include many errors and bugs

If you have one of these, you can visit the [issues](https://github.com/L-fyz/Mist/issues)
Also you can do pull requests with your code. You'r welcome!
