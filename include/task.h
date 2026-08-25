#ifndef TASK_H
#define TASK_H

/* Task lifecycle states - mirrors a real RTOS/OS process state machine */
typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_TERMINATED
} TaskState;

/* Task Control Block (TCB) - core OS data structure */
typedef struct Task {
    int id;
    int priority;          /* 0 = highest priority (like most RTOS conventions) */
    int burst_time;        /* total simulated CPU time required (ms) */
    int remaining_time;
    int arrival_time;
    int completion_time;
    TaskState state;
    struct Task *next;     /* intrusive linked-list pointer used by TaskQueue */
} Task;

Task *task_create(int id, int priority, int burst_time, int arrival_time);
void  task_destroy(Task *t);
const char *task_state_str(TaskState s);

#endif /* TASK_H */
