#include <functional>
#include<prioirity_queue>
// Version 2 : Using priority queue in C++ STL.
extern void set_hw_timer(int relative_time_us);
extern int current_time_us();

class Task {
public:
    std::function<void()> callback;
    int execute_at;
    
    Task(std::function<void()> callback, int execute_at) : callback(callback), execute_at(execute_at) {}
};

class Compare {
public:
    bool operator()(Task t1, Task t2) {
        return t1.execute_at > t2.execute_at;
    }
};

// STL uses max heap by default, so we need to define a min heap by using > in the comparison.
std::priority_queue<Task, std::vector<Task>, Compare> TaskQueue;

void schedule(void (*callback)(), int delay_us) {
    Task new_task(callback, delay_us + current_time_us());
    TaskQueue.push(new_task);
    set_next_timer();
}

void set_next_timer() {
    if (!TaskQueue.empty()) {
        Task next_task = TaskQueue.top();
        int delay = next_task.execute_at - current_time_us();
        set_hw_timer(delay);
    }
}

void hw_timer_handler() {
    while (!TaskQueue.empty() && TaskQueue.top().execute_at <= current_time_us()) {
        Task task = TaskQueue.top();
        TaskQueue.pop();
        task.callback();
    }
    set_next_timer();
}