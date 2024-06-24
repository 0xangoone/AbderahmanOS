#include "tty.h"
#include "cpu.h"
#include "sound.h"
char* vga_buffer = (char*)0xb8000;
unsigned char cur_color = 0;
extern "C" int chars_written = 0;

extern "C" void tty_char_print(char w){
    if (w == 0) return;
    if (chars_written == HIGHT * WIDTH)
        chars_written = 0;
    int cur_x = (chars_written % WIDTH);
    char* current_write_index = (char*)0xb8000+(chars_written*2);
    *(current_write_index+1) = cur_color;
    if (w == '\n'){
        int space = WIDTH - cur_x - 1;
        for (int i = 0 ;i<space;i++)
            tty_char_print(' ');
            chars_written++;
        return;
    }else if (w == '\t'){
        for (int i = 0 ;i<4;i++)
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
    char numb[20];
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
extern "C" void tty_hex_print(unsigned int number){
    tty_print("0x");
    int hexa[20];
    int i = 0;
    while( number != 0){
        hexa[i] = number % 16;
        number = number / 16;
        i++;
    }

    while (i > 0) {
        int cur = hexa[--i];
        char index;
        if ( cur >= 0 && cur <= 9 ){
            index = (char)cur+'0';
        }else{
            switch (cur) {
                case 10:
                    index = 'A';
                    break;
                case 11:
                    index = 'B';
                    break;
                case 12:
                    index = 'C';
                    break;
                case 13:
                    index = 'D';
                    break;
                case 14:
                    index = 'E';
                    break;
                case 15:
                    index = 'F';
                    break;
                default:
                    break;
            }
        }

        tty_char_print(index);
    }

    return;
}
extern "C" void panic(char* error,char* details,int code){
    change_text_color(colors::white,colors::blue);

    tty_print(
"           ___  ____   ____   ___   ____   \n"
" __       /  _]|    \ |    \ /   \ |    \  \n"
"|  |     /  [_ |  D  )|  D  )     ||  D  ) \n"
"|__|    |    _]|    / |    /|  O  ||    /  \n"
" __     |   [_ |    \ |    \|     ||    \  \n"
"|  |    |     ||  .  \|  .  \     ||  .  \ \n"
"|__|    |_____||__|\_||__|\_|\___/ |__|\_| \n"

);
    tty_print(
"       __\n"
"  _   / /\n"
" (_) | | \n"
"     | | \n"
"  _  | | \n"
" (_) | | \n"
"      \_\\\n"
    );
    tty_print("an Bug Detected :!\n");
    tty_print("Bug code: ");tty_hex_print(code);
    tty_print("\nBug name: ");tty_print(error);
    tty_print("\ndetails about Bug: ");tty_print(details);

    Regs regs = get_regs();
    tty_print("\neax: ");tty_hex_print(regs.eax);
    tty_print("\necx: ");tty_hex_print(regs.ecx);
    tty_print("\nebx: ");tty_hex_print(regs.ebx);
    tty_print("\nedx: ");tty_hex_print(regs.edx);
    //playsound(200);
    beep(200,20);
}

