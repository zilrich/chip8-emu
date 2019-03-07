#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include "../inc/display.h"
#include "../inc/utils.h"

bool framebuffer[FB_HEIGHT][FB_WIDTH];
pthread_t timerthread;

int main() {
    short *mem = malloc(0x7FF);
    loadrom(mem);
    reginit();
    pthread_create(&timerthread, NULL, timers, NULL);
    displayinit();
    while(exec(mem));
    free(mem);
    endwin();

    return 0;
}


