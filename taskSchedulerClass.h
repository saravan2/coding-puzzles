#include <functional>
#include <vector>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <cTimeFunctions.h>

class Task {
public:
    std::function<void()> callback;
    int execute_at;
    
    Task(std::function<void()> callback, int execute_at) : callback(callback), execute_at(execute_at) {}
    ~Task() = default;
};

class Compare {
public:
    Compare() = default;
    ~Compare() = default;

    bool operator()(Task t1, Task t2) {
        return t1.execute_at > t2.execute_at;
    }
};

// STL uses max heap by default, so we need to define a min heap by using > in the comparison.
class Scheduler {
public:
    Scheduler() = default;
    ~Scheduler() = default;

private:
    std::priority_queue<Task, std::vector<Task>, Compare> TaskQueue;
    std::mutex	mtx;
    std::condition_variable	cv;
    int next_timer_us{0};
    std::atomic<unsigned long long> mtx_head{0};
    std::atomic<unsigned long long> mtx_tail{0};

    /* Ensures threads don't get starved */
    void scheduler_fair_lock() {
        std::unique_lock<std::mutex> lck(this->mtx);
        unsigned long long turn = this->mtx_tail++;
        cv.wait(lck, (turn != this->mtx_head));
    }

    /* Wake up the next thread in line */
    void scheduler_fair_unlock() {
        std::unique_lock<std::mutex> lck(mtx);
        this->mtx_head++;
        cv.notify_all();
    }

    void set_next_timer() {
        if (!TaskQueue.empty()) {
            Task next_task = TaskQueue.top();
            // Prevents frivolous set_hw_timer() when TaskQueue's top
            // has not changed after a push() in schedule()
            if (next_task.execute_at != this->next_timer_us) {
                this->next_timer_us = next_task.execute_at - current_time_us();
                set_hw_timer(this->next_timer_us);
            }
        }
    }

public:
    void schedule(void (*callback)(), int delay_us) {
        fair_scheduler_mutex_lock();
        Task new_task(callback, delay_us + current_time_us());
        TaskQueue.push(new_task);
        set_next_timer();
        scheduler_fair_unlock();
    }

    void execute_tasks() {
        scheduler_fair_lock();
        while (!TaskQueue.empty() && TaskQueue.top().execute_at <= current_time_us()) {
            Task task = TaskQueue.top();
            TaskQueue.pop();
            task.callback();
        }
        set_next_timer();
        scheduler_fair_unlock();
    }
};