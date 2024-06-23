#include "types.h"
// 8 bit value
extern "C" void outb(uint16_t port, uint8_t data){
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
	return;
}

extern "C" uint8_t inb(uint16_t port){
	uint8_t res;
	asm volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}

// 16 bit value
extern "C" void outw(uint16_t port, uint16_t value)
{
	asm volatile ("outw %w0, %1" : : "a" (value), "id" (port) );
}

extern "C" uint16_t inw(uint16_t port){
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// 32 bit value

extern "C" void outl(uint16_t port, uint32_t value){
	asm volatile ("outl %%eax, %%dx" :: "d" (port), "a" (value));
}

extern "C" uint32_t inl(uint16_t port){
   uint32_t ret;
   asm volatile ("inl %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
