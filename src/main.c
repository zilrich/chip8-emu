#include "../inc/main.h"

u8 *mem;
bool debug;

int main(int argc, char *argv[]) {
    mem = malloc(0x1000);
    LoadROM(argv[1]);
    pthread_create(&timer_thread, NULL, timers, NULL);
    InitDigits();
    DisplayInint();
    if (argc == 3) if (*argv[2] == 'd') debug = true;
    while (Exec());
    free(mem);

    return 0;
}


