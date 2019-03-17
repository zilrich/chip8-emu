#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

#include <stdbool.h>

int displayinit();
int displayrefresh();
int draw(u8 *mem, u8 x, u8 y, u8 size);