#define OP (*addr >> 12)
#define NNN (*addr & 0x0FFF)
#define N (*addr & 0x000F)
#define X (*addr & 0x0F00 >> 8)
#define Y (*addr & 0x00F0 >> 4)
#define KK (*addr & 0x00FF)

typedef unsigned char u8;
typedef unsigned short u16;

extern u16 *mem;

extern u8 V[0xF];

extern u16 I;

extern u8 DT;
extern u8 ST;

extern u16 PC;

extern u8 SP;
extern u16 stack[16];

int reginit();
int loadrom(u16 *mem);
void *timers(void *param);
int exec(u16 *mem);