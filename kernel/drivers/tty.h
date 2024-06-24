#define WIDTH 80
#define HIGHT 25
extern "C" void tty_char_print(char w);
extern "C" void change_text_color( unsigned char for_color , unsigned char bac_color);
extern "C" void clear_tty();
extern "C" void tty_print(char* msg);
extern "C" void tty_udecimal_print(unsigned int number);
extern "C" void tty_hex_print(unsigned int number);
extern "C" void panic(char* error,char* details,int code);
enum colors{
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    pink,
    yellow,
    white,
};

