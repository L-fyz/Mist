#include <mist.h>

void __attribute__((section(".text.start"), noreturn)) main(void) {
    clear();
    print("Welcome to Mist!");
    print("\nMist - tiny x86_86 operating system");
    print("\nNow it have:");
    print("\n1. Paging");
    print("\n2. GDT");
    print("\n3. Screen work tools");
    print("\n4. Memory work tools");
    print("\n5. VGA driver");
    for(;;) __asm__ volatile("hlt");
}
