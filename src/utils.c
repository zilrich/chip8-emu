#include <stdio.h>
#include <unistd.h>
#include "../inc/header.h"

u16 *mem;

u8 V[0xF];

u16 I;

u8 DT;
u8 ST;

u16 PC;

u8 SP;
u16 stack[16];

int reginit() {
    u8 V[0xF] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    u16 I = 0;

    u8 DT = 0;
    u8 ST = 0;

    u16 PC = 0x200;

    u8 SP = 0;
    u16 stack[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    return 0;
}

int loadrom(u16 *mem) {
    FILE *rom = fopen("./rom.ch8", "r");
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

