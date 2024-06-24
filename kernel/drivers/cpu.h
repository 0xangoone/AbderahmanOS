typedef struct Regs{
  int eax;
  int ebx;
  int ecx;
  int edx;
}Regs;
extern "C" void shutdown();
extern "C" void reboot();
extern "C" Regs get_regs();
extern "C" unsigned long read_tsc();
extern "C" void sleep(int time);
