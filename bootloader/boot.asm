[org 7c00h]
[bits 16]

KERNEL_LOCATION equ 0x1000
BOOT_DISK: db 0
_start:
    mov [BOOT_DISK],dl
    jmp load_kernel
load_kernel:
    xor ax,ax
    mov es,ax
    mov ds,ax
    mov bp,0x8000
    mov sp,bp

    mov bx,KERNEL_LOCATION
    mov dh,20

    mov ah,0x02
    mov al,dh
    mov ch,0x00
    mov dh,0x00
    mov cl,0x02
    mov dl,[BOOT_DISK]
    int 0x13

	xor si,si
	jc disk_fail
text_mode:
    mov ah,0x00
    mov al, 0x3
    int 0x10
gdt_init:
    cli
	lgdt[gdt_descriptor]
	mov eax, cr0
	or al, 0x01
	mov cr0, eax
	jmp CODE_SEG:start_protected_mode


CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

gdt_start:
gdt_null:
	dd 0x00
	dd 0x00
gdt_code:
	dw 0xFFFF
	dw 0x00
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00
gdt_data:
	dw 0xFFFF
	dw 0x00
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00
gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start


[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov ebp, 0x90000
	mov esp, ebp


	jmp KERNEL_LOCATION
disk_fail:
	mov ah,0x0e
	mov al,[si + msg]
	int 10h
	inc si
	cmp al,00
	jne disk_fail
	jmp $
msg: db "code: 0x00000001 _error while reading the bootdisk !",00
times 510-($-$$) db 0x00
dw 0xAA55
