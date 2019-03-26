#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "../inc/header.h"

u16 keydown(SDL_Event event);
u16 keyup(SDL_Event event);

extern bool framebuffer[FB_WIDTH][FB_HEIGHT];
extern bool timer;

SDL_Event event;

bool keypressed[0x12];

int counter = 0;

int exec(u8 *mem, bool debug) {
    bool increment = 1;
    bool disupdate = 0; 
    char tempchar;
    u16 *temp = mem + PC;
    u16 addr =  __builtin_bswap16(*temp);
    if (debug) printf("%4X PC = %4X\n", addr, PC);

    if (debug) printmem();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return 0;
        else if (event.type == SDL_KEYDOWN) keydown(event);
        else if (event.type == SDL_KEYUP) keyup(event);
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
            u16 temptimer = timer;
            while (temptimer == timer)
            break;
        case 0xE:
            switch (KK) {
                case 0x9E:
                    if (keypressed[V[X]]) PC += 2;
                    break;
                case 0xA1:
                    if (keypressed[V[X]] == false) PC += 2;
                    break;
            }
            break;
        case 0xF:
            switch (KK) {
                case 0x07://LD
                    V[X] = DT;
                    break;
                case 0x0A://LD
                    while (1) {
                        SDL_PollEvent(&event);
                        if (event.type == SDL_KEYDOWN) {
                            u16 keypressed = keydown(event);
                            if (keypressed > 0x10) continue;
                            else {
                                V[X] = keypressed;
                                break;
                            }
                        }
                    }
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
                    I = V[X] * 5;
                    break;
                case 0x33://LD
                    *(mem + I) = V[X] / 100;
                    *(mem + I + 1) = (V[X] / 10) % 10;
                    *(mem + I + 2) = V[X] % 10;
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
    if (debug) {
        while (1) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) return 0;
                else if (event.type == SDL_KEYDOWN) keydown(event);
            }
            if (keypressed[0x10]) {
                keypressed[0x10] = false;
                break;
            }
            else if (keypressed[0x11]) {
                usleep(5000);
                break;
            }
        }
        return 1;
    }
}

u16 keydown(SDL_Event event) {
    switch (event.key.keysym.sym){
        case SDLK_x:
            keypressed[0x0] = true;
            return 0x0;
        case SDLK_1:
            keypressed[0x1] = true;
            return 0x1;
        case SDLK_2:
            keypressed[0x2] = true;
            return 0x2;
        case SDLK_3:
            keypressed[0x3] = true;
            return 0x3;
        case SDLK_q:
            keypressed[0x4] = true;
            return 0x4;
        case SDLK_w:
            keypressed[0x5] = true;
            return 0x5;
        case SDLK_e:
            keypressed[0x6] = true;
            return 0x6;
        case SDLK_a:
            keypressed[0x7] = true;
            return 0x7;
        case SDLK_s:
            keypressed[0x8] = true;
            return 0x8;
        case SDLK_d:
            keypressed[0x9] = true;
            return 0x9;
        case SDLK_z:
            keypressed[0xA] = true;
            return 0xA;
        case SDLK_c:
            keypressed[0xB] = true;
            return 0xB;
        case SDLK_4:
            keypressed[0xC] = true;
            return 0xC;
        case SDLK_r:
            keypressed[0xD] = true;
            return 0xD;
        case SDLK_f:
            keypressed[0xE] = true;
            return 0xE;
        case SDLK_v:
            keypressed[0xF] = true;
            return 0xF;
        case SDLK_p:
            keypressed[0x10] = true;
        case SDLK_o:
            keypressed[0x11] = true;
        default:
            return 0x10;
    }
}

u16 keyup(SDL_Event event) {
    switch (event.key.keysym.sym){
        case SDLK_x:
            keypressed[0x0] = false;
            return 0x0;
        case SDLK_1:
            keypressed[0x1] = false;
            return 0x1;
        case SDLK_2:
            keypressed[0x2] = false;
            return 0x2;
        case SDLK_3:
            keypressed[0x3] = false;
            return 0x3;
        case SDLK_q:
            keypressed[0x4] = false;
            return 0x4;
        case SDLK_w:
            keypressed[0x5] = false;
            return 0x5;
        case SDLK_e:
            keypressed[0x6] = false;
            return 0x6;
        case SDLK_a:
            keypressed[0x7] = false;
            return 0x7;
        case SDLK_s:
            keypressed[0x8] = false;
            return 0x8;
        case SDLK_d:
            keypressed[0x9] = false;
            return 0x9;
        case SDLK_z:
            keypressed[0xA] = false;
            return 0xA;
        case SDLK_c:
            keypressed[0xB] = false;
            return 0xB;
        case SDLK_4:
            keypressed[0xC] = false;
            return 0xC;
        case SDLK_r:
            keypressed[0xD] = false;
            return 0xD;
        case SDLK_f:
            keypressed[0xE] = false;
            return 0xE;
        case SDLK_v:
            keypressed[0xF] = false;
            return 0xF;
        case SDLK_p:
            keypressed[0x10] = false;
        case SDLK_o:
            keypressed[0x11] = false;
        default:
        
            return 0x10;
    }
}