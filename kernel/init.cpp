#include "drivers/drivers.h"

extern "C" void kernel_main() {
    change_text_color(colors::blue,colors::yellow);
    tty_print("Welcome to ZeroOS\n");
    change_text_color(colors::black,colors::red);
    tty_print("this os was developed by 0xAngoOne\n");


    tty_print("write your name: ");
    char* name = "           \0";
    input(name ,11,false);
    tty_print("hello mr ");tty_print(name);
    panic("failed to read memory location .","an program try to write on a valid memory location",0x265EF);
    reboot();

    return;
}
