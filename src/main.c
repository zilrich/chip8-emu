#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include "../inc/header.h"

extern bool framebuffer[FB_HEIGHT][FB_WIDTH];
pthread_t timerthread;

int main() {
    u16 *mem = malloc(0x7FF);
    loadrom(mem);
    reginit();
    pthread_create(&timerthread, NULL, timers, NULL);
    displayinit();
    while(exec(mem));
    free(mem);
    printf("for some reason finished\n");
    sleep(2);
    endwin();

    return 0;
}


