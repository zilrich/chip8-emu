#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

typedef unsigned char u8;
typedef unsigned short u16;

extern bool framebuffer[FB_HEIGHT][FB_WIDTH];
int displayinit();
int displayrefresh();
int draw(u8 x, u8 y, u16 size);