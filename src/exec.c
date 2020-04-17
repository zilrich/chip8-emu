#include "../inc/exec.h"

int Exec() {
    bool increment = 1;
    bool display_update = 0;
    u16 *temp = (u16 *) mem + PC;
    u16 instruction =  __builtin_bswap16(*temp);
    if (debug) {
        printf("%4X PC = %4X\n", instruction, PC);
        PrintMem();
    }

    while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) return 0;
    const u8 *pkKeyboardState = SDL_GetKeyboardState(NULL);
    if (instruction == 0x0000)	return 0;
    switch (OP) {
        case 0x0:
            switch (instruction) {
                case 0x00E0://CLS
                    memset(framebuffer, 0 , FB_SIZE);
                    display_update = 1;
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
            Draw(V[X], V[Y], N);
            display_update = 1;
            break;
        case 0xE:
            switch (KK) {
                case 0x9E:
                    if (pkKeyboardState[kKeyMap[V[X]]]) PC += 2;
                    break;
                case 0xA1:
                    if (!pkKeyboardState[kKeyMap[V[X]]]) PC += 2;
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
                            u16 temp_key = Keypress();
                            if (temp_key > 0x10) continue;
                            else {
                                V[X] = temp_key;
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
    if (display_update) DisplayRefresh();
    if (debug) {
        while (1) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) return 0;
            }
            pkKeyboardState = SDL_GetKeyboardState(NULL);
            if (pkKeyboardState[kKeyMap[0x10]]) {
                usleep(250000);
                break;
            }
            else if (pkKeyboardState[kKeyMap[0x11]]) {
                usleep(5000);
                break;
            }
        }
    }
    usleep(1900);
    return 1;
}

u8 Keypress() {
    switch (event.key.keysym.scancode){
        case SDL_SCANCODE_X: return 0x0;
        case SDL_SCANCODE_1: return 0x1;
        case SDL_SCANCODE_2: return 0x2;
        case SDL_SCANCODE_3: return 0x3;
        case SDL_SCANCODE_Q: return 0x4;
        case SDL_SCANCODE_W: return 0x5;
        case SDL_SCANCODE_E: return 0x6;
        case SDL_SCANCODE_A: return 0x7;
        case SDL_SCANCODE_S: return 0x8;
        case SDL_SCANCODE_D: return 0x9;
        case SDL_SCANCODE_Z: return 0xA;
        case SDL_SCANCODE_C: return 0xB;
        case SDL_SCANCODE_4: return 0xC;
        case SDL_SCANCODE_R: return 0xD;
        case SDL_SCANCODE_F: return 0xE;
        case SDL_SCANCODE_V: return 0xF;
        case SDL_SCANCODE_P: return 0x10;
        case SDL_SCANCODE_O: return 0x11;
        default: return 0x12;
    }
}
