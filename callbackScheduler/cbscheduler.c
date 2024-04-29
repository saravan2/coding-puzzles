#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <timer.h>
#include "cbscheduler.h"

#define TQ_OK 0
#define TQ_ERR -1

// Structs
typedef struct {
    void (*callback)();
    uint64_t execute_at;
} Task;

typedef struct {
    Task *tasks;
    unsigned int size;
    unsigned int capacity;
    timer_t tq_timerid;
    uint64_t tq_timer_at;
    pthread_mutex_t tq_mutex;
    pthread_cond_t tq_cond;
    unsigned long long tq_mutex_head;
    unsigned long long tq_mutex_tail;
} TaskPQ;

// Globals
TaskPQ tq* = NULL;
volatile unsigned int tq_shutdown = 1;

// Declarations
static uint64_t get_current_time_in_us();
static void tq_fair_mutex_lock();
static void tq_fair_mutex_unlock();
static void tq_fair_mutex_unlock();
static int tq_set_timer();
static int tq_resize();
static void tq_bubble_up(unsigned int index);
static void tq_bubble_down(unsigned int index);
static void tq_remove(unsigned int index);
static int tq_push(Task T)
static Task tq_pop();
static Task tq_front();
static void timer_thread(void * arg);


static uint64_t get_current_time_in_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*(uint64_t)1000000 + tv.tv_usec;
}

static void tq_fair_mutex_lock() {
    if (tq) {
        pthread_mutex_lock(&tq->tq_mutex);
        unsigned long long turn = tq->tq_mutex_tail++;
        while (turn != tq->tq_mutex_head) {
            pthread_cond_wait(&tq->tq_cond, &tq->tq_mutex);
        }
    }
}

static void tq_fair_mutex_unlock() {
    if (tq) {
        tq->tq_mutex_head++;
        pthread_cond_broadcast(&tq->tq_cond);
        pthread_mutex_unlock(&tq->tq_mutex);
    }

}
static int tq_set_timer() {
    int status = TQ_ERR;
    if (tq && tq->size && !tq_shutdown) {
        Task t = tq->tasks[0];
        if (t.execute_at != tq->tq_timer_at) {
            uint64_t current_time_us = get_current_time_in_us();
            uint64_t delay_us = (t.execute_at > current_time_us)?(t.execute_at - current_time_us):1;
            struct itimerspec its;
            its.it_interval.tv_sec = 0;
            its.it_interval.tv_nsec = 0;
            its.it_value.tv_sec = delay_us / 1000000ULL;
            its.it_value.tv_nsec = (delay_us % 1000000ULL) * 1000ULL;
            
            if (timer_settime(&tq->tq_timerid, 0, &its, NULL)) {
                perror("tq_set_timer() - Failed to set timer");
            } else {
                tq->tq_timer_at = t.execute_at;
                status = TQ_OK;
            }
        }
    }
    return status;
}

static int tq_resize() {
    int status = TQ_ERR;
    if (tq) {
        unsigned int nc = TQ_RESIZE_FACTOR * tq->capacity;
        Task *nq = (Task*)realloc(tq->tasks, nc * sizeof(Task));
        if (!nq) {
            perror("tq_resize() - Resizing failed");
            return status;
        }
        tq->tasks = nq;
        tq->capacity = nc;
        status = TQ_OK;
    }
    return status;
}

static void tq_bubble_up(unsigned int index) {
    if (tq) {
        while(index > 0) {
            unsigned int parent = (index - 1) / 2;
            if (tq->tasks[index].execute_at < tq->tasks[parent].execute_at) {
                Task temp = tq->tasks[index];
                tq->tasks[index] = tq->tasks[parent];
                tq->tasks[parent] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }
}

static void tq_bubble_down(unsigned int index) {
    if (tq) {
        unsigned int n = tq->size;
        while (index < n) {
            unsigned int left = (2 * index) + 1;
            unsigned int right = (2 * index) + 2;
            int smallest = index;

            if (left < n && tq->tasks[left].execute_at < tq->tasks[smallest].execute_at) {
                smallest = left;
            }

            if (right < n && tq->tasks[right].execute_at < tq->tasks[smallest].execute_at) {
                smallest = right;Can we implement a hashing function
            }

            if (smallest != index) {
                Task temp = tq->tasks[index];
                tq->tasks[index] = tq->tasks[smallest];
                tq->tasks[smallest] = temp;
                index = smallest;
            } else {
                break;
            }
        }
    }
}

static void tq_remove(unsigned int index) {
    if (tq && tq->size \
        && index >= 0 \
        && index < tq->size) {
        tq->tasks[index] = tq->tasks[--tq->size];
        if (index) {
            // Compare with parent to know whether bubble up or down
            int parent = (index - 1) / 2;
            if (tq->tasks[index].execute_at < tq->tasks[parent].execute_at) {
                tq_bubble_up(index);
            } else {
                tq_bubble_down(index);
            }
        } else {
            tq_bubble_down(index);
        }
    }
}

static int tq_push(Task T) {
    int status = TQ_ERR;
    if (tq) {
        if (tq->size == tq->capacity) {
            status = tq_resize();
            if (status) {
                return status;
            }
        }
        // Add to the bottom of the priority queue
        tq->tasks[tq->size] = T;
        tq_bubble_up(tq->size);
        // Increment the size after bubbling up
        tq->size++;
        status = TQ_OK;
    }
    return status;
}

static Task tq_pop() {
    Task t = {NULL, 0};
    if (tq && tq->size) {
        t = tq->tasks[0];
        tasks[0] = tq->tasks[--tq->size];
        // Decrement the size before bubbling down
        tq_bubble_down(0);
    }
    return t;
}

static Task tq_front() {
    Task t = {NULL, 0};
    if (tq && tq->size) {
        t = tq->tasks[0];
    }
    return t;
}

static void timer_thread(void * arg) {
    if (tq && !tq_shutdown) {
        uint64_t current_time_us = get_current_time_in_us();
        tq_fair_mutex_lock();
        while(!tq_shutdown) {
            Task t = tq_front();
            if (t.callback == NULL) {
                break;
            }
            if (t.execute_at <= current_time_us) {
                t = tq_pop();
                t.callback();
            } else {
                break;
            }
        }
        if (tq_set_timer()) {
            perror("timer_thread() - Failed to set timer");
        }
        tq_fair_mutex_unlock();
    }
}

void cbscheduler_init() {
    struct sigevent sev;

    tq = (TaskPQ* )malloc(sizeof(TaskPQ));
    if (!tq) {
        perror("cbscheduler_init() - Failed to allocate memory for TaskPQ");
        exit(TQ_ERR);
    }
    tq->tasks = (Task*)malloc(TQ_INIT_CAPACITY * sizeof(Task));
    if (!(tq->tasks)) {
        perror("cbscheduler_init() - Failed to allocate memory for TaskPQ tasks");
        exit(TQ_ERR);
    }
    tq->size = 0;
    tq->capacity = TQ_INIT_CAPACITY;
    tq->tq_timerid = 0;
    tq->tq_timer_at = 0;
    if (pthread_mutex_init(&tq->tq_mutex, NULL)) {
        perror("cbscheduler_init() - Failed to initialize tq mutex");
        exit(TQ_ERR);
    }

    if (pthread_cond_init(&tq->tq_cond, NULL)) {
        perror("cbscheduler_init() - Failed to initialize tq conditional variable");
        exit(TQ_ERR);
    }
    tq->tq_mutex_head = 0;
    tq->tq_mutex_tail = 0;
        
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_notify_function = timer_thread;
    sev.sigev_value.sival_ptr = NULL;

    if (timer_create(CLOCK_REALTIME, &sev, &tq->tq_timerid) == TQ_ERR) {
        perror("cbscheduler_init() - Failed to create timer");
        exit(TQ_ERR);
    }

    tq_shutdown = 0;
}

void cbscheduler_shutdown() {
    tq_shutdown = 1;
    // Wait for timer thread and threads registering callback to exit critical section.
    sleep(2);
    if (tq) {
        tq_fair_mutex_lock();
        tq_fair_mutex_unlock();
        if (tq->tq_timerid) {
            if (timer_delete(&tq->tq_timerid)) {
                perror("cbscheduler_shutdown() - Failed to disarm tq timer !");
            }
        }
        if (pthread_mutex_destroy(&tq->tq_mutex)) {
            perror("cbscheduler_shutdown() - Failed to destroy tq mutex");
        }
        if (pthread_cond_destroy(&tq->tq_cond)) {
            perror("cbscheduler_shutdown() - Failed to destroy tq conditional variable");
        }
        if (tq->tasks) {
            free(tq->tasks);
        }
        free(tq);
        tq = NULL;
    }
}

int schedule(void (*callback)(), uint64_t delay_us)  {
    int status = TQ_ERR;
    if (callback && delay_us) {
        Task T = {callback, get_current_time_in_us() + delay_us};
        if (tq && !tq_shutdown) {
            tq_fair_mutex_lock();

            if (tq_push(T)) {
                perror("schedule() - Failed to push task");
            } else {
                if (tq_set_timer()) {
                    perror("schedule() - Failed to set timer after pushing task");
                } else {
                    status = TQ_OK;
                }
            }

            tq_fair_mutex_unlock();
        }
    }
    return status;
}
