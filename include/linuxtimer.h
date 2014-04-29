#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <time.h>
#define NANOS 1000000000LL

static struct timespec startTime, endTime;
static long long begin;
static double elapsed;

void startTimer();
void stopTimer();
void resetTimer();
double getElapsedTime();

#endif // TIMER_H
