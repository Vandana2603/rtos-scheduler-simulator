#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

/* Priority-sorted singly linked list used as the scheduler's ready queue.
 * This is the core "Data Structures" showcase for the project:
 * insertion keeps tasks ordered by priority, and FIFO order is preserved
 * among tasks of equal priority (stable insert). */
typedef struct {
    Task *head;
    int   count;
} TaskQueue;

void  queue_init(TaskQueue *q);
void  queue_push_sorted(TaskQueue *q, Task *t);
Task *queue_pop_front(TaskQueue *q);
int   queue_is_empty(const TaskQueue *q);
void  queue_print(const TaskQueue *q);
void  queue_free_all(TaskQueue *q);

#endif /* QUEUE_H */
