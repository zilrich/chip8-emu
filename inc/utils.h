#define OP (addr >> 12)
#define N (addr & 0x000F)
#define X ((addr & 0x0F00) >> 8)
#define Y ((addr & 0x00F0) >> 4)
#define KK (addr & 0x00FF)
#define NNN (addr & 0x0FFF)
#define OFFSET 0x200

typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *mem;

extern u8 V[0x10];

extern u16 I;

extern u8 DT;
extern u8 ST;

extern u16 PC;

extern u8 SP;
extern u16 stack[0x10];

int initdigits();
int loadrom(u8 *mem, char *path);
void *timers(void *param);
int printmem();