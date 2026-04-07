bits 16
org 0x7C00

start:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7000

    in al, 0x92
    or al, 2
    out 0x92, al

    sti
    mov si, dap
    mov ah, 0x42
    mov dl, 0x80
    int 0x13
    cli

    lgdt [gdt_ptr]

    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp 0x08:p_m

bits 32
p_m:
    mov ax, 0x10
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov esp, 0x90000

    mov eax, 0x100000
    mov ebx, 0x10000
    mov ecx, 32768
    .kernel_load:
        mov edi, [ebx]
        mov [eax], edi
        add eax, 4
        add ebx, 4
        loop .kernel_load

    mov edi, 0x1000
    mov dword [edi], 0x2003
    mov dword [edi+4], 0

    mov edi, 0x2000
    mov dword [edi], 0x3003
    mov dword [edi+4], 0

    mov edi, 0x3000
    mov ebx, 0x00000083
    mov ecx, 512
.pd_loop:
    mov dword [edi], ebx
    mov dword [edi+4], 0
    add ebx, 0x200000
    add edi, 8
    loop .pd_loop

    mov eax, 0x1000
    mov cr3, eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    jmp 0x18:lm_entry

bits 64
lm_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov rsp, 0x90000

    mov rax, 0x100000
    call rax

    cli
.halt:
    hlt
    jmp .halt

dap:
    db 0x10
    db 0
    dw 127
    dw 0x0000
    dw 0x1000
    dq 1

gdt_start:
    dq 0

gdt_code32:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data32:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_code64:
    dw 0x0000
    dw 0x0000
    db 0x00
    db 10011010b
    db 00100000b
    db 0x00
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510 - ($ - $$) db 0
dw 0xAA55
