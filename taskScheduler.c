#include<taskScheduler.h>

// Threads can register callbacks
void schedule(void (*callback)(), int delay_us) {
    schedule_task(callback, delay_us);
}

// ISR context
void hw_timer_handler() {
    execute_tasks();
}

