#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include "../inc/header.h"

extern bool framebuffer[FB_HEIGHT][FB_WIDTH];
extern int counter;
pthread_t timerthread;

int main() {
    u8 *mem = malloc(0xFFF);
    loadrom(mem);
    pthread_create(&timerthread, NULL, timers, NULL);
    displayinit();
    while(exec(mem));
    free(mem);
    endwin();
    printf("executed %d intructions\n", counter);
    sleep(2);

    return 0;
}


