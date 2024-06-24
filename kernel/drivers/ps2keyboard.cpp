#include "drivers.h"

extern "C" int read_ps2keyboard_scancode(){
    int code = inb(0x60);
    return code;
}
extern "C" int chars_written;
extern "C" char ps2kyscan_to_char(int scan){
    switch ( scan ){
        case keys::delet:
            chars_written -= 1;
            tty_char_print(' ');
            chars_written -= 1;
            return 0;
    };
    char c = scan_to_ch[scan];
    return c;
}
extern "C" void input(char* ptr,int size,bool stop_on_enter){
        int i = 0;
        bool is_released = false;
        char last_char;
        while(true){
            if (is_released){
                int scan = read_ps2keyboard_scancode();
                char c = ps2kyscan_to_char(scan);
                if (scan == 0xE0){
                    is_released = !is_released;
                    continue;
                }
                if (i >= size){
                    return;
                }
                else if (!stop_on_enter && c == '\n'){
                    tty_char_print(c);
                    return;
                }
                else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || ( c == ' ' || c == '\t')){
                    if ( last_char == 'd' && c == 's')  {last_char='s';continue;}
                    tty_char_print(c);
                    last_char = c;
                    ptr[i] = c;
                    i++;
                }
            }
            is_released = !is_released;
            int time = 1;
            unsigned long freq = 200000000;
            unsigned long cycles = freq * time;
            unsigned long start = read_tsc();
            while (read_tsc() - start < cycles);
        }
        return;
}
