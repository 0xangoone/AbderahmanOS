[bits 32]
[extern kernel_main]
[extern stty_print]
[extern stty_char_print]
global _start
section .text
;sys_call table
_start:
    jmp near main
    jmp near stty_print ; _start + 0x003
    jmp near stty_char_print ; _start + 0x008

main:
    call kernel_main
    jmp $
