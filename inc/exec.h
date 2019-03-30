#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "types.h"
#define OP (addr >> 12)
#define N (addr & 0x000F)
#define X ((addr & 0x0F00) >> 8)
#define Y ((addr & 0x00F0) >> 4)
#define KK (addr & 0x00FF)
#define NNN (addr & 0x0FFF)
#define OFFSET 0x200
#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

u16 keypress(bool state);
int printmem();

int displayinit();
int displayrefresh();
int draw(u8 x, u8 y, u8 size);

extern bool framebuffer[FB_WIDTH][FB_HEIGHT];
extern bool timer;

SDL_Event event;

bool keypressed[0x12];

int counter;

extern u8 *mem;

extern u8 V[0x10];
extern u16 I;
extern u8 DT;
extern u8 ST;
extern u16 PC;
extern u8 SP;
extern u16 stack[0x10];

extern bool debug;