#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "../inc/header.h"

extern int counter;
pthread_t timerthread;

int exec(u8 *mem, bool slow);

int main(int argc, char *argv[]) {
    bool debug = false;
    u8 *mem = malloc(0x1000);
    loadrom(mem, argv[1]);
    pthread_create(&timerthread, NULL, timers, NULL);
    initdigits(mem);
    displayinit();
    if (argc == 3) if (*argv[2] == 'd') debug = true;
    while (exec(mem, debug));
    free(mem);
    if (debug) {
        printf("executed %d intructions\n", counter);
    }

    return 0;
}


