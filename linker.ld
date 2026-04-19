OUTPUT_FORMAT("elf64-x86-64")
ENTRY(main)

SECTIONS {
    . = 0x100000;

    .text : {
        *(.text.start)
        *(.text)
        *(.text.*)
    }

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }

    .data : {
        *(.data)
        *(.data.*)
    }

    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note)
        *(.eh_frame)
    }
}
