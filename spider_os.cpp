#include "spider_os.h"

uint32_t OS_GetTickCount()
{
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    return OS_TimeToTickCount(ts);   
}

uint32_t OS_TicksPerSecond(){
	return 1000;
}

uint32_t OS_TimeToTickCount(struct timespec ts) {
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void OS_SleepTicks(uint32_t sleep_time) {
    uint32_t us = (sleep_time / OS_TicksPerSecond()) * 1000000;
    usleep(us);
}


