#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define TQ_INIT_CAPACITY 10
#define TQ_RESIZE_FACTOR 2

// Function prototypes

// Initializes the callback scheduler
void cbscheduler_init();

// Schedules a callback to be executed after a delay in microseconds
// Returns 0 on success, -1 on failure
int schedule(void (*callback)(), uint64_t delay_us);

// Shuts down the callback scheduler
void cbscheduler_shutdown();

#endif