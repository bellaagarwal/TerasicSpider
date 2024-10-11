#ifndef SPIDER_OS_H_
#define SPIDER_OS_H_

#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/**
 * Get the current wall clock time, in units of OS ticks.
 * This time can be safely compared to timestamps from
 * input events, once converted to the same units.
 * 
 * A larger number indicates a later time.
 */
uint32_t OS_GetTickCount();

/**
 * Returns the number of OS ticks in a single second,
 * can be used to translate between seconds & OS ticks.
 */
uint32_t OS_TicksPerSecond();

/**
 * Given a timestamp in seconds/nanoseconds, converts it to OS ticks.
 */
uint32_t OS_TimeToTickCount(struct timespec ts);

/**
 * Put the program to sleep (and thus consuming less power)
 * for a number of OS ticks.
 * @param sleep_time - the number of OS ticks to put this program to sleep for.
 */
void OS_SleepTicks(uint32_t sleep_time);


#endif //SPIDER_OS_H_
