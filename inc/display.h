#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "types.h"
#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

extern u8 *mem;

extern u16 I;
extern u8 V[0x10];