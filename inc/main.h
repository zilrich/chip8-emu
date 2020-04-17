#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "types.h"

pthread_t timer_thread;

int Exec();

int LoadROM(char *path);
void *timers(void *param);
int InitDigits();

int DisplayInint();
