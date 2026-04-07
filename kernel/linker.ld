OUTPUT_FORMAT("elf64-x86-64")
ENTRY(main)

SECTIONS {
    . = 0x100000;  /* Ядро начнётся с виртуального адреса 1MB */

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
