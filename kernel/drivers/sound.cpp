#include "ports.h"
#include "cpu.h"
extern "C" void playsound(unsigned int nFrequence) {
    unsigned short x;
    unsigned char y;

    x = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (unsigned char)(x));
    outb(0x42, (unsigned char)(x >> 8));
    y = inb(0x61);
    if (y != (y | 3)) {
        outb(0x61, y | 3);
    }
}

extern "C" void speakerquiet() {
    unsigned char x = inb(0x61) & 0xFC;
    outb(0x61, x);
}
extern "C" void beep(int freq,int time){
    if (freq == 0)  return;
    if (time == 0)  return;
    playsound(freq);
    sleep(time);
    speakerquiet();
}
