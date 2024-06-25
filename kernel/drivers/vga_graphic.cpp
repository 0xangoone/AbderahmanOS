    // some sources : https://wiki.osdev.org/VGA_Hardware

    /*
     *  -----------------------------------
     *
     *   simple VGA driver
     *
     *  0xAngoone
     *
     *
     *
     * -------------------------------------
     */

#include "drivers.h"



void DisableDisplay() {
    outb(0x3C0, 0x00);
    outb(0x3C0, 0x00);
}

void UnlockCRTC() {
    outb(0x3D4, 0x11);
    unsigned char value = inb(0x3D5);
    outb(0x3D5, value & 0x7F);
}

void Loadmode13Registers() {

    outb(0x3C2, 0x63);  // Miscellaneous Output Register

    outb(0x3C4, 0x00); outb(0x3C5, 0x03);  // Synchronous Reset
    outb(0x3C4, 0x01); outb(0x3C5, 0x01);  // Clocking Mode
    outb(0x3C4, 0x02); outb(0x3C5, 0x0F);  // Enable Write to all Planes
    outb(0x3C4, 0x03); outb(0x3C5, 0x00);  // Character Map Select
    outb(0x3C4, 0x04); outb(0x3C5, 0x0E);  // Memory Mode

    outb(0x3CE, 0x00); outb(0x3CF, 0x00);  // Set/Reset Register
    outb(0x3CE, 0x01); outb(0x3CF, 0x00);  // Enable Set/Reset
    outb(0x3CE, 0x02); outb(0x3CF, 0x00);  // Color Compare
    outb(0x3CE, 0x03); outb(0x3CF, 0x00);  // Data Rotate
    outb(0x3CE, 0x04); outb(0x3CF, 0x00);  // Read Map Select
    outb(0x3CE, 0x05); outb(0x3CF, 0x40);  // Mode Register
    outb(0x3CE, 0x06); outb(0x3CF, 0x05);  // Miscellaneous
    outb(0x3CE, 0x07); outb(0x3CF, 0x0F);  // Color Don't Care
    outb(0x3CE, 0x08); outb(0x3CF, 0xFF);  // Bit Mask

    outb(0x3D4, 0x00); outb(0x3D5, 0x5F);  // Horizontal Total
    outb(0x3D4, 0x01); outb(0x3D5, 0x4F);  // Horizontal Display End
    outb(0x3D4, 0x02); outb(0x3D5, 0x50);  // Horizontal Blanking Start
    outb(0x3D4, 0x03); outb(0x3D5, 0x82);  // Horizontal Blanking End
    outb(0x3D4, 0x04); outb(0x3D5, 0x54);  // Horizontal Retrace Start
    outb(0x3D4, 0x05); outb(0x3D5, 0x80);  // Horizontal Retrace End
    outb(0x3D4, 0x06); outb(0x3D5, 0xBF);  // Vertical Total
    outb(0x3D4, 0x07); outb(0x3D5, 0x1F);  // Overflow
    outb(0x3D4, 0x08); outb(0x3D5, 0x00);  // Preset Row Scan
    outb(0x3D4, 0x09); outb(0x3D5, 0x41);  // Maximum Scan Line
    outb(0x3D4, 0x10); outb(0x3D5, 0x9C);  // Vertical Retrace Start
    outb(0x3D4, 0x11); outb(0x3D5, 0x8E);  // Vertical Retrace End
    outb(0x3D4, 0x12); outb(0x3D5, 0x8F);  // Vertical Display End
    outb(0x3D4, 0x13); outb(0x3D5, 0x28);  // Logical Screen Width
    outb(0x3D4, 0x14); outb(0x3D5, 0x40);  // Underline Location
    outb(0x3D4, 0x15); outb(0x3D5, 0x96);  // Vertical Blanking Start
    outb(0x3D4, 0x16); outb(0x3D5, 0xB9);  // Vertical Blanking End
    outb(0x3D4, 0x17); outb(0x3D5, 0xA3);  // Mode Control

    outb(0x3C0, 0x10); outb(0x3C0, 0x41);  // Mode Control
    outb(0x3C0, 0x11); outb(0x3C0, 0x00);  // Overscan Register
    outb(0x3C0, 0x12); outb(0x3C0, 0x0F);  // Color Plane Enable
    outb(0x3C0, 0x13); outb(0x3C0, 0x00);  // Horizontal Panning
    outb(0x3C0, 0x14); outb(0x3C0, 0x00);  // Color Select
    outb(0x3C0, 0x20);  // Enable Display
}

void ClearScreen() {
    unsigned char* VRAM = (unsigned char*)0xA0000;
    for (int i = 0; i < 320 * 200; ++i) {
        VRAM[i] = 0;
    }
}

void LockCRTC() {
    outb(0x3D4, 0x11);
    unsigned char value = inb(0x3D5);
    outb(0x3D5, value | 0x80);
}

void EnableDisplay() {
    outb(0x3C0, 0x20);
}

extern "C" void set_vga_to_graphic_mode13() {
    DisableDisplay();
    UnlockCRTC();
    Loadmode13Registers();
    ClearScreen();
    LockCRTC();
    EnableDisplay();
}

extern "C" void set_pixel_mode13(int x, int y, unsigned char color) {
    unsigned char* VRAM = (unsigned char*)0xA0000;
    unsigned char* Pixel = VRAM + (y * 320) + x;
    *Pixel = color;
}
extern "C" void draw_array(int h[],int len){
    // number 300 = new line .......
    int i = 0;
    int x = 0;
    int y = 0;
    while(i < len){
        if (h[i] == 300){y++;i++;x=0;continue;}
        set_pixel_mode13(x,y,h[i]);
        x++;
        i++;
    }
}
