#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <timer.h>
#include "cbscheduler.h"

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
static void tq_set_timer();
static void tq_resize();
static void tq_bubble_up();
static void tq_bubble_down();
static void tq_push(Task T);
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
static void tq_set_timer() {
    if (tq && tq->size && !tq_shutdown) {
        Task t = tq->tasks[0];
        uint64_t current_time_us = get_current_time_in_us();
        uint64_t delay_us = (t.execute_at > current_time_us)?(t.execute_at - current_time_us):1;
        struct itimerspec its;
        its.it_value.tv_sec = 0;
        its.it_value.tv_nsec = 1000ULL*delay_us;
        its.it_interval.tv_sec = 0;

        if (timer_settime(&tq->tq_timerid, 0, &its, NULL) == -1) {
            perror("Failed to set timer");
            exit(-1);
        }
    }
}

static void tq_resize() {
    if (tq) {
        unsigned int nc = TQ_RESIZE_FACTOR * tq->capacity;
        Task *nq = (Task*)realloc(tq->tasks, nc * sizeof(Task));
        if (nq == tq->tasks) {
            perror("Resizing tq failed");
            exit(-1);
        }
        tq->tasks = nq;
        tq->capacity = nc;
    }
}

static void tq_bubble_up() {
    if (tq) {
        unsigned int index = tq->size;
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

static void tq_bubble_down() {
    if (tq) {
        unsigned int n = tq->size;
        unsigned int index = 0;
        while (index < n) {
            unsigned int left = (2 * index) + 1;
            unsigned int right = (2 * index) + 2;
            int smallest = index;

            if (left < n && tq->tasks[left].execute_at < tq->tasks[smallest].execute_at) {
                smallest = left;
            }

            if (right < n && tq->tasks[right].execute_at < tq->tasks[smallest].execute_at) {
                smallest = right;
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

static void tq_push(Task T) {
    if (tq) {
        if (tq->size == tq->capacity) {
            tq_resize();
        }
        // Add to the bottom of the priority queue
        tq->tasks[tq->size] = T;
        tq_bubble_up();
        // Increment the size after bubbling up
        tq->size++;
    }
}

static Task tq_pop() {
    Task t = {NULL, 0};
    if (tq && tq->size) {
        t = tq->tasks[0];
        tasks[0] = tq->tasks[--tq->size];
        // Decrement the size before bubbling down
        tq_bubble_down();
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
        tq_set_timer();
        tq_fair_mutex_unlock();
    }
}

void cbscheduler_init() {
    struct sigevent sev;

    tq = (TaskPQ* )malloc(sizeof(TaskPQ));
    if (!tq) {
        perror("Failed to allocate memory for TaskPQ");
        exit(-1);
    }
    tq->tasks = (Task*)malloc(TQ_INIT_CAPACITY * sizeof(Task));
    if (!(tq->tasks)) {
        perror("Failed to allocate memory for TaskPQ tasks\n");
        exit(-1);
    }
    tq->size = 0;
    tq->capacity = TQ_INIT_CAPACITY;
    tq->tq_timerid = 0;
    if (pthread_mutex_init(&tq->tq_mutex, NULL)) {
        perror("Failed to initialize tq mutex");
        exit(-1);
    }

    if (pthread_cond_init(&tq->tq_cond, NULL)) {
        perror("Failed to initialize tq conditional variable");
        exit(-1);
    }
    tq->tq_mutex_head = 0;
    tq->tq_mutex_tail = 0;
        
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_notify_function = timer_thread;
    sev.sigev_value.sival_ptr = NULL;

    if (timer_create(CLOCK_REALTIME, &sev, &tq->tq_timerid) == -1) {
        perror("Failed to create timer");
        exit(-1);
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
                perror("Failed to disarm tq timer !");
            }
        }
        if (pthread_mutex_destroy(&tq->tq_mutex)) {
            perror("Failed to destroy tq mutex !");
        }
        if (pthread_cond_destroy(&tq->tq_cond)) {
            perror("Failed to destroy tq conditional variable !");
        }
        if (tq->tasks) {
            free(tq->tasks);
        }
        free(tq);
        tq = NULL;
    }
}

void schedule(void (*callback)(), uint64_t delay_us)  {
    if (callback && delay_us) {
        Task T = {callback, get_current_time_in_us() + delay_us};
        if (tq && !tq_shutdown) {
            tq_fair_mutex_lock();
            tq_push(T);
            tq_set_timer();
            tq_fair_mutex_unlock();
        }
    }
}
