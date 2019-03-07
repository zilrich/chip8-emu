#define FB_WIDTH 64
#define FB_HEIGHT 32
#define FB_SIZE FB_WIDTH * FB_HEIGHT

extern bool framebuffer[FB_HEIGHT][FB_WIDTH];
int displayinit();
int displayrefresh();
int draw(char x, char y, short size);