#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../inc/header.h"

bool timer = false;

u8 *mem;

u8 V[0x10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

u16 I = 0;

u8 DT = 0;
u8 ST = 0;

u16 PC = OFFSET;

u8 SP = 0;
u16 stack[0x10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

u8 digits[] = {0xF0, 0x90, 0x90, 0x90, 0xF0, //0
               0x20, 0x60, 0x20, 0x20, 0x70, //1
               0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
               0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
               0x90, 0x90, 0xF0, 0x10, 0x10, //4
               0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
               0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
               0xF0, 0x10, 0x20, 0x40, 0x40, //7
               0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
               0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
               0xF0, 0x90, 0xF0, 0x90, 0x90, //A
               0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
               0xF0, 0x80, 0x80, 0x80, 0xF0, //C
               0xE0, 0x90, 0x90, 0x90, 0xE0, //D
               0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
               0xF0, 0x80, 0xF0, 0x80, 0x80};//F

int loadrom(u8 *mem, char *path) {
    FILE *rom = fopen(path, "r");
    fseek(rom, 0, SEEK_END);
    long int size = ftell(rom);
    fseek(rom, 0, SEEK_SET);
    fread(mem + OFFSET, 1, size, rom);
    fclose(rom);

    return 0;
}

void *timers(void *param) {
    while (1) {
        if (DT) DT--;
        if (ST) ST--;
        timer = !timer;
        usleep(16670);
    }
}

int initdigits(u8 *mem) {
    for (u8 i = 0; i < 80; i++) {
        *(mem + i) = digits[i];
    }

    return 0;
}

int printmem() {
    for (int i = 0; i < 16; i++) {
        printf("V[%d]: %d       ", i, V[i]);
        if (i == 0) printf("PC: %d", PC);
        else if (i == 1) printf("I: %d", I);
        printf("\n");
    }

    return 0;
}