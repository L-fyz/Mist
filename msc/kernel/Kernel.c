#include "mist.h"

void __attribute__((section(".text.start"), noreturn)) main(void) {
    clear();
    print("                         @#");
    print("\n              %(        }##");
    print("\n             ##>       <#:#");
    print("\n            #01#      ## ##");
    print("\n           &# ##     ##  <>");
    print("\n          #?  ##    ##    /n");
    print("\n         >#    ##  ##      [#");
    print("\n        #@     (# #)        #^");
    print("\n      ?*        -_-          #*#");
    print("\n    #&                        $##%");
    print("\n  <#                            #0#1");
    print("\n#@                                #+#=]");
    print("\n                                    {#!#}");
    print("\n                                      ?#@;#{");
    print("\n -- Welcome to Mist!");
    print("\n\nStarting...");

    if (!pmm_init()) {
        print("\n[ - ]: PMM initialization");
        for (;;) __asm__ volatile("hlt");
    } else {
        print("\n[ + ]: PMM initialization");
    }

    if (!vmm_init()) {
        print("\n[ - ]: VMM initialization");
        for (;;) __asm__ volatile("hlt");
    } else {
        print("\n[ + ]: VMM initialization");
    }
    for (;;) __asm__ volatile("hlt");
}
