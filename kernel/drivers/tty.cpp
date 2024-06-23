#include "tty.h"
char* vga_buffer = (char*)0xb8000;
unsigned char cur_color = 0;
int chars_written = 0;

extern "C" void tty_char_print(char w){
    int cur_x = (chars_written % WIDTH);
    char* current_write_index = (char*)0xb8000+(chars_written*2);
    *(current_write_index+1) = cur_color;
    if (w == '\n'){
        int space = WIDTH - cur_x - 1;
        for (int i = 0 ;i<space;i++)
            tty_char_print(' ');
            chars_written++;
        return;
    }
    *current_write_index = w;
    chars_written++;
    return;
}
extern "C" void change_text_color( unsigned char for_color , unsigned char bac_color){
    cur_color = for_color | (bac_color << 4);


}
extern "C" void clear_tty(){
   unsigned short* i = (unsigned short*)0xb8000;

    for (; (unsigned int)i < 0xb8000 + chars_written * 2; i++) {
        *i = (15 << 8) | ' ';
    }
    change_text_color(15,0);
    chars_written = 0;

}
extern "C" void tty_print(char* msg){
    int i = 0;
    while (msg[i] != '\0'){
        tty_char_print(msg[i]);
        i++;
    }
    return ;
}
extern "C" void tty_udecimal_print(unsigned int number) {
    char numb[10];
    int j = 0;
    while (number != 0) {
        int digit = number % 10;
        number /= 10;
        numb[j]=(char)digit+'0';
        j++;
    }
    if (j == 0) {
        numb[j++] = '0';
    }
    while (j > 0) {
        tty_char_print(numb[--j]);
    }
    return;
}

