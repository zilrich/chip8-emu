#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "types.h"

#define OP (addr >> 12)
#define N (addr & 0x000F)
#define X ((addr & 0x0F00) >> 8)
#define Y ((addr & 0x00F0) >> 4)
#define KK (addr & 0x00FF)
#define NNN (addr & 0x0FFF)
#define OFFSET 0x200

extern u8 *mem;