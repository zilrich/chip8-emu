#include "../inc/main.h"

u8 *mem;
bool debug;

int main(int argc, char *argv[]) {
    mem = malloc(0x1000);
    loadrom(argv[1]);
    pthread_create(&timerthread, NULL, timers, NULL);
    initdigits();
    displayinit();
    if (argc == 3) if (*argv[2] == 'd') debug = true;
    while (exec());
    free(mem);

    return 0;
}


