#include <linuxtimer.h>

void startTimer()
{
	if(startTime.tv_sec == 0 && startTime.tv_nsec == 0)
	{
		clock_gettime(CLOCK_REALTIME, &startTime);
		begin = startTime.tv_sec*NANOS + startTime.tv_nsec;
	}
}

void stopTimer()
{
	clock_gettime(CLOCK_REALTIME, &endTime);
	elapsed = (double)((endTime.tv_sec*NANOS + endTime.tv_nsec) - begin)/NANOS;
}

void resetTimer()
{
	startTime.tv_sec = 0;
	startTime.tv_nsec = 0;
}

double getElapsedTime()
{
	return elapsed;
}


