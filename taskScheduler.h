#ifdef __cplusplus
extern "C" {
#endif

void scheduler_init();
void scheduler_cleanup();
void schedule_task(void (*callback)(), int delay_us);
void execute_tasks();

#ifdef __cplusplus
}
#endif