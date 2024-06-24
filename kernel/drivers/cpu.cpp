#include "cpu.h"
extern "C" Regs get_regs(){
    Regs out;
    __asm__ __volatile__ ("mov %%eax,%0" : "=r" (out.eax));
    __asm__ __volatile__ ("mov %%ebx,%0" : "=r" (out.ebx));
    __asm__ __volatile__ ("mov %%ecx,%0" : "=r" (out.ecx));
    __asm__ __volatile__ ("mov %%edx,%0" : "=r" (out.edx));
    return out;
}
extern "C" unsigned long read_tsc(){
    unsigned int hi,lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo),"=d"(hi));
    return (unsigned long)(hi << 32) | lo;
}
extern "C" void sleep(int time){
    unsigned long freq = 2500000000;
    unsigned long cycles = freq * time;
    unsigned long start = read_tsc();
    while (read_tsc() - start < cycles);
}
