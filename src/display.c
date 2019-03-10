#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ncurses.h>
#include "../inc/header.h"

bool framebuffer[FB_HEIGHT][FB_WIDTH];

int displayinit() {
    WINDOW *win = initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    raw();
    noecho();
    nodelay(win, TRUE);
    curs_set(0);

    return 0;
}

int displayrefresh() {
    printf("in displayrefresh\n");
    sleep(1);
    for (int y = 0; y <= FB_HEIGHT; y++) {
        for (int x = 0; x <= FB_WIDTH; x++) {
            if (framebuffer[y][x]) {
                attron(COLOR_PAIR(1));
                mvprintw(y, 2 * x, "  ");
                attroff(COLOR_PAIR(1));
            }
            else {
                mvprintw(y, 2 * x, "  ");
            }
        }
    }
    refresh();

    printf("done\n");
    sleep(1);

    return 0;
}

int draw(u8 *mem, u8 x, u8 y, u16 size) {
    for (u8 i = 0; i < size; i++) {
        y++;
        char tempx;
        tempx = x;
        bool tempval;
        if (y > FB_HEIGHT) y = 0;
        for (u8 a = 0; a < 8; a++) {
            if (tempx > FB_WIDTH) tempx = 0;
            tempval = (*(mem + I + i) & (0x80 >> a)) >> (7 - a);
            V[0xF] = (tempval & framebuffer[y][tempx]) ? 1 : 0;
            framebuffer[y][tempx] ^= tempval;
            tempx++;
        }
    }

    return 0;
}
