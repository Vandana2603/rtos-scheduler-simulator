#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"

Task *task_create(int id, int priority, int burst_time, int arrival_time)
{
    Task *t = (Task *)malloc(sizeof(Task));
    if (!t) {
        fprintf(stderr, "task_create: out of memory\n");
        exit(EXIT_FAILURE);
    }
    t->id              = id;
    t->priority        = priority;
    t->burst_time      = burst_time;
    t->remaining_time  = burst_time;
    t->arrival_time    = arrival_time;
    t->completion_time = -1;
    t->state           = TASK_READY;
    t->next            = NULL;
    return t;
}

void task_destroy(Task *t)
{
    free(t);
}

const char *task_state_str(TaskState s)
{
    switch (s) {
        case TASK_READY:      return "READY";
        case TASK_RUNNING:    return "RUNNING";
        case TASK_BLOCKED:    return "BLOCKED";
        case TASK_TERMINATED: return "TERMINATED";
        default:              return "UNKNOWN";
    }
}
