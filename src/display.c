#include "../inc/display.h"

bool framebuffer[FB_WIDTH][FB_HEIGHT];
SDL_Renderer* renderer;
SDL_Window* window;

int DisplayInint() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("chip8", 0, 0, 640, 320, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_RenderSetLogicalSize(renderer, 640, 320);
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return 0;
}

int DisplayRefresh() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 10;
    rect.h = 10;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (u8 y = 0; y < FB_HEIGHT; y++) {
        for (u8 x = 0; x < FB_WIDTH; x++) {
            if (framebuffer[x][y]) {
                rect.x = x * 10;
                rect.y = y * 10;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);

    return 0;
}

int Draw(u8 x, u8 y, u8 size) {
    bool sprite[8][size];
    bool temp = 0;
    u8 wx = x;
    u8 wy = y;
    V[0xF] = false;

    for (u8 i = 0; i < size; i++) {
        for (u8 j = 0;  j < 8; j++){
            temp = (*(mem + I + i) & (0x80 >> j)) >> (7 - j);
            sprite[j][i] = temp;
        }
    }
    for (u8 i = 0; i < size; i++) {
        if (wy == FB_WIDTH) wy = 0;
        for (u8 j = 0; j < 8; j++) {
            if (wx == FB_WIDTH) wx = 0;
            if (framebuffer[wx][wy] && sprite[j][i]) V[0xF] = true;
            framebuffer[wx][wy] ^= sprite[j][i];
            wx++;
        }
        wx = x;
        wy++;
    }

    return 0;
}
