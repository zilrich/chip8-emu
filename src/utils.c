#include <stdio.h>
#include <unistd.h>
#include "../inc/utils.h"

int reginit() {
    char V[0xF] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    short I = 0;

    char DT = 0;
    char ST = 0;

    short PC = 0x200;

    char SP = 0;
    short stack[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    return 0;
}

int loadrom() {
    FILE *rom = fopen("rom.ch8", "r");
    fseek(rom, 0, SEEK_END);
    long int size = ftell(rom);
    fseek(rom, 0, SEEK_SET);
    fread(mem, 1, size, rom);
    fclose(rom);

    return 0;
}

void *timers(void *param) {
    while (1) {
        if (DT) DT--;
        if (ST) ST--;
        usleep(16670);
    }
}
