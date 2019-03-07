#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "../inc/utils.h"
#include "../inc/display.h"

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

int draw(char x, char y, short size) {
    for (short i = 0; i < size; i++) {
        short *addr = mem + I + i;
        char *target = &framebuffer[y + i][x];
        *target = *addr;
    }

    return 0;
}
