char* vga_buffer = (char*)0xb8000;
int chars_written = 0;
extern "C" void stty_char_print(char w){
    char* current_write_index = (char*)0xb8000+(chars_written*2);
    *current_write_index = w;
    chars_written++;
    return;
}
extern "C" void stty_print(char* msg){
    int i = 0;
    while (msg[i] != '\0'){
        stty_char_print(msg[i]);
        i++;
    }
    return ;
}
