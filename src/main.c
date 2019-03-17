#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "../inc/header.h"

extern int counter;
pthread_t timerthread;

int main(int argc, char *argv[]) {
    u8 *mem = malloc(0xFFF);
    loadrom(mem, argv[1]);
    pthread_create(&timerthread, NULL, timers, NULL);
    keymap();
    displayinit();
    while(exec(mem));
    free(mem);
    printf("executed %d intructions\n", counter);
    sleep(2);

    return 0;
}


