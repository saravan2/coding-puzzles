#ifndef SCHEDULER_H
#define SCHEDULER_H

#define TQ_INIT_CAPACITY 10
#define TQ_RESIZE_FACTOR 2

void cbscheduler_init();
void schedule(void (*callback)(), uint64_t delay_us);

#endif
#endif