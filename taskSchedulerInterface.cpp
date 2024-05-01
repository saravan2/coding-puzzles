#include<taskScheduler.h>
#include<taskSchedulerClass.h>

#ifdef __cplusplus
extern "C" {
#endif

static Scheduler scheduler_instance = NULL;

void scheduler_init() {
    scheduler_instance = new Scheduler();
}

void scheduler_cleanup() {
    if (scheduler_instance) {
        delete scheduler_instance;
        scheduler_instance = NULL;
    }
}

/* Can be invoked from threads */
void schedule_task(void (*callback)(), int delay_us) {
    if (scheduler_instance) {
        scheduler_instance->schedule(callback, delay_us);
    }
}

/* From ISR context, when set_hw_timer() expires */
void execute_tasks() {
    if (scheduler_instance) {
        scheduler_instance->execute_tasks();
    }
}

#ifdef __cplusplus
}
#endif