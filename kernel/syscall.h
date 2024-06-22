// syscall table functions

typedef void (*PrintFunction)(const char*);
PrintFunction tty_print = (PrintFunction)(0x1000 + 3);

typedef void (*PrintCharFunction)(char);
PrintCharFunction tty_char_print = (PrintCharFunction)(0x1000 + 8);
