#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "../inc/header.h"

bool framebuffer[FB_HEIGHT][FB_WIDTH];

int displayinit() {
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    raw();
    noecho();
    curs_set(0);

    return 0;
}

int displayrefresh() {
    int x, y;
    x = 0;
    y = 0;
    while (y < FB_HEIGHT) {
        x++;
        if (x >= FB_WIDTH) {
            x = 0;
            y++;
            continue;
        }
        if (framebuffer[y][x]) {
            attron(COLOR_PAIR(1));
            mvprintw(y, 2 * x, "  ");
            attroff(COLOR_PAIR(1));
        }
        else {
            mvprintw(y, 2 * x, "  ");
        }
    }
    refresh();

    return 0;
}

int draw(u16 *mem, u8 x, u8 y, u16 size) {
    for (u16 i = 0; i < size; i++) {
        u16 *addr = mem + I + i;
        u8 *target = &framebuffer[y + i][x];
        *target = *addr;
    }

    return 0;
}
