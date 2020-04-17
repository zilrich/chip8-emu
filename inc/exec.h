#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "types.h"
#define OP (instruction >> 12)
#define N (instruction & 0x000F)
#define X ((instruction & 0x0F00) >> 8)
#define Y ((instruction & 0x00F0) >> 4)
#define KK (instruction & 0x00FF)
#define NNN (instruction & 0x0FFF)
#define OFFSET 0x200
#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

u8 Keypress();
int PrintMem();

int DisplayInint();
int DisplayRefresh();
int Draw(u8 x, u8 y, u8 size);

extern bool framebuffer[FB_WIDTH][FB_HEIGHT];
extern bool timer;

SDL_Event event;

bool key_pressed[0x12];

extern u8 *mem;

extern u8 V[0x10];
extern u16 I;
extern u8 DT;
extern u8 ST;
extern u16 PC;
extern u8 SP;
extern u16 stack[0x10];

extern bool debug;

const SDL_Scancode kKeyMap[] = {
    SDL_SCANCODE_X, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3,
    SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_A,
    SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_Z, SDL_SCANCODE_C,
    SDL_SCANCODE_4, SDL_SCANCODE_R, SDL_SCANCODE_F, SDL_SCANCODE_V,
    SDL_SCANCODE_P, SDL_SCANCODE_O
};
