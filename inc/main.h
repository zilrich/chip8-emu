#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "types.h"

extern int counter;
pthread_t timerthread;

int exec();

int loadrom(char *path);
void *timers(void *param);
int initdigits();

int displayinit();