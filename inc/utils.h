#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "types.h"

#define OP (instruction >> 12)
#define N (instruction & 0x000F)
#define X ((instruction & 0x0F00) >> 8)
#define Y ((instruction & 0x00F0) >> 4)
#define KK (instruction & 0x00FF)
#define NNN (instruction & 0x0FFF)
#define OFFSET 0x200

extern u8 *mem;
