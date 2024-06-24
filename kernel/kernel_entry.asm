[bits 32]
[extern kernel_main]
global _start
global reboot
global shutdown
section .text
_start:
    call kernel_main
    jmp $
reboot:
    mov al,0xFE
    out 0x64,al
    hlt
    jmp reboot
shutdown:
    mov al,0xF4
    out 0xB004,al
    hlt
