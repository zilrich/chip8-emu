#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "../inc/header.h"

extern bool framebuffer[FB_WIDTH][FB_HEIGHT];

SDL_Event event;

int counter = 0;

u8 key[256];

int keymap() {
    key[','] = 0x0;
    key['7'] = 0x1;
    key['8'] = 0x2;
    key['9'] = 0x3;
    key['u'] = 0x4;
    key['i'] = 0x5;
    key['o'] = 0x6;
    key['j'] = 0x7;
    key['k'] = 0x8;
    key['l'] = 0x9;
    key['m'] = 0xA;
    key['.'] = 0xB;
    key['0'] = 0xC;
    key['p'] = 0xD;
    key[';'] = 0xE;
    key['/'] = 0xF;
}

int exec(u8 *mem) {
    bool increment = 1;
    bool disupdate = 0;
    char tempchar;
    u16 *temp = mem + PC;
    u16 addr =  __builtin_bswap16(*temp);
    //printf("%4X PC = %4X\n", addr, PC);

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
        return 0;
    }
    if (addr == 0x0000) return 0;
    switch (OP) {
        case 0x0:
            switch (addr) {
                case 0x00E0://CLS
                    memset(framebuffer, 0 , FB_SIZE);
                    disupdate = 1;
                    break;
                case 0x00EE://RET
                    PC = stack[SP];
                    SP--;
                    break;
            }
            break;
        case 0x1://JP
            PC = NNN;
            increment = 0;
            break;
        case 0x2://CALL
            SP++;
            stack[SP] = PC;
            PC = NNN;
            increment = 0;
            break;
        case 0x3://SE
            if (V[X] == KK) PC += 2;
            break;
        case 0x4://SNE
            if (V[X] != KK) PC += 2;
            break;
        case 0x5://SE
            if (V[X] == V[Y]) PC += 2;
            break;
        case 0x6://LD
            V[X] = KK;
            break;
        case 0x7://ADD
            V[X] += KK;
            //printf("Vx = V[0x%1X] kk = 0x%2X\n", X, KK);
            break;
        case 0x8:
            switch (N) {
                case 0x0://LD
                    V[X] = V[Y];
                    break;
                case 0x1://OR
                    V[X] = V[X] | V[Y];
                    break;
                case 0x2://AND
                    V[X] = V[X] & V[Y];
                    break;
                case 0x3://XOR
                    V[X] = V[X] ^ V[Y];
                    break;
                case 0x4://ADD
                    V[0xF] = ( (u16) V[X] + V[Y] > 255) ? 1: 0;
                    V[X] = V[X] + V[Y];
                    break;
                case 0x5://SUB
                    V[0xF] = ( (u16) V[X] > V[Y]) ? 1: 0;
                    V[X] = V[X] - V[Y];
                    break;
                case 0x6://SHR
                    V[0xF] = (V[X] % 2) ? 1: 0;
                    V[X] /= 2;
                    break;
                case 0x7://SUBN
                    V[0xF] = (V[Y] > V[X]) ? 1: 0;
                    V[X] = V[Y] - V[X];
                    break;
                case 0xE://SHL
                    V[0xF] = (V[X] > 0x7F) ? 1: 0;
                    V[X] *= 2;
                    break;
            }
            break;
        case 0x9://SNE
            if (V[X] != V[Y]) PC += 2;
            break;
        case 0xA://LD
            I = NNN;
            break;
        case 0xB://JP
            PC = NNN + V[0x0];
            increment = 0;
            break;
        case 0xC://RND
            V[X] = (u8) (rand() % 256) & KK;
            break;
        case 0xD://DRW
            draw(mem, V[X], V[Y], N);
            disupdate = 1;
            break;
        case 0xE:
            switch (KK) {
                case 0x9E:
                    break;
                case 0xA1:
                    break;
            }
            break;
        case 0xF:
            switch (KK) {
                case 0x07://LD
                    V[X] = DT;
                    break;
                case 0x0A://LD
                    tempchar = getchar();
                    V[X] = key[tempchar];
                    break;
                case 0x15://LD
                    DT = V[X];
                    break;
                case 0x18://LD
                    ST = V[X];
                    break;
                case 0x1E://ADD
                    I += V[X];
                    break;
                case 0x29://LD
                    I = X * 5;
                    break;
                case 0x33://LD
                    *(mem + I) = X / 100;
                    *(mem + I + 1) = (X / 10) % 10;
                    *(mem + I + 2) = X % 10;
                    break;
                case 0x55://LD
                    for (u8 i = 0; i <= X; i++) {
                        *(mem + I + i) = V[i];
                    }
                    break;
                case 0x65://LD
                    for (u8 i = 0; i <= X; i++) {
                        V[i] = *(mem + I + i);
                    }
                    break;
            }
            break;
    }

    if (increment) PC += 2;
    counter++;
    int zero = 0;
    if (disupdate) displayrefresh();

    return 1;
}