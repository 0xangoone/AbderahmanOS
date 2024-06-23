[bits 32]
[extern kernel_main]
global _start
section .text
_start:
    call kernel_main
    jmp $
