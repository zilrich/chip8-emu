#define OP (*addr >> 12)
#define NNN (*addr & 0x0FFF)
#define N (*addr & 0x000F)
#define X (*addr & 0x0F00 >> 8)
#define Y (*addr & 0x00F0 >> 4)
#define KK (*addr & 0x00FF)

extern short *mem;

extern char V[0xF];

extern short I;

extern char DT;
extern char ST;

extern short PC;

extern char SP;
extern short stack[16];

int reginit();
int loadrom();
void *timers(void *param);
int exec();