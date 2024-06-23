#include "drivers/drivers.h"
extern "C" void kernel_main() {
    playsound(300);
    change_text_color(colors::blue,colors::yellow);
    tty_print("Welcome to ZeroOS\n");
    change_text_color(colors::black,colors::red);
    tty_print("this os was developed by 0xAngoOne\n");
    tty_udecimal_print(7581);
    return;
}
