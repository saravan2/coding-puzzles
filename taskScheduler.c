// Got stumped when I was asked to implement a task scheduler in a C++ interview.
// Coding it down here to make sure I don't forget it.

extern void set_hw_timer(int relative_time_us);
extern int current_time_us();

// Version 1 : Using linked list.

typedef struct {
    void (*callback)();
    int execute_at;
} Task;

typedef struct {
    Task task;
    struct TaskNode* next;
} TaskNode;

TaskNode* TaskList = NULL;

void insert_task(TaskNode* new_task) {
    TaskNode* current = TaskList;
    TaskNode* previous = NULL;
    
    while (current != NULL && current->task.execute_at < new_task->task.execute_at) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        new_task->next = TaskList;
        TaskList = new_task;
    } else {
        previous->next = new_task;
        new_task->next = current;
    }
}

void set_next_timer() {
    if (TaskList != NULL) {
        TaskNode* next_task = TaskList;
        int delay = next_task->task.execute_at - current_time_us();
        set_hw_timer(delay);
    }
}

void schedule(void (*callback)(), int delay_us) {
    TaskNode* new_task = (TaskNode*)malloc(sizeof(TaskNode));
    new_task->task.callback = callback;
    new_task->task.execute_at = delay_us + current_time_us();
    new_task->next = NULL;
    insert_task(new_task);
    set_next_timer();
}

void hw_timer_handler() {
    while (TaskList != NULL && TaskList->task.execute_at <= current_time_us()) {
        TaskNode* task = TaskList;
        TaskList = TaskList->next;
        task->task.callback();
        free(task);
    }
    set_next_timer();
}

