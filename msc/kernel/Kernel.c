#include "mist.h"

void __attribute__((section(".text.start"), noreturn)) main(void) {
    clear();
    print_str("                         @#");
    print_str("\n              %(        }##");
    print_str("\n             ##>       <#:#");
    print_str("\n            #01#      ## ##");
    print_str("\n           &# ##     ##  <>");
    print_str("\n          #?  ##    ##    /n");
    print_str("\n         >#    ##  ##      [#");
    print_str("\n        #@     (# #)        #^");
    print_str("\n      ?*        -_-          #*#");
    print_str("\n    #&                        $##%");
    print_str("\n  <#                            #0#1");
    print_str("\n#@                                #+#=]");
    print_str("\n                                    {#!#}");
    print_str("\n                                      ?#@;#{");
    print_str("\n -- Welcome to Mist!");
    print_str("\n\nStarting...");

    if (!pmm_init()) {
        print_str("\n[FAIL]: PMM initialization");
        for (;;) __asm__ volatile("hlt");
    } else {
        print_str("\n[ OK ]: PMM initialization");
    }

    if (!vmm_init()) {
        print_str("\n[FAIL]: VMM initialization");
        for (;;) __asm__ volatile("hlt");
    } else {
        print_str("\n[ OK ]: VMM initialization");
    }
    for (;;) __asm__ volatile("hlt");
}
