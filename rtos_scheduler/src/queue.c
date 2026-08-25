#include <stdio.h>
#include "../include/queue.h"

void queue_init(TaskQueue *q)
{
    q->head  = NULL;
    q->count = 0;
}

/* Stable insert-sort by priority (lower value = higher priority).
 * Equal-priority tasks keep FIFO order -> gives round-robin behaviour
 * when the scheduler repeatedly pops/pushes a preempted task. */
void queue_push_sorted(TaskQueue *q, Task *t)
{
    t->next = NULL;

    if (q->head == NULL || t->priority < q->head->priority) {
        t->next = q->head;
        q->head = t;
        q->count++;
        return;
    }

    Task *cur = q->head;
    while (cur->next != NULL && cur->next->priority <= t->priority) {
        cur = cur->next;
    }
    t->next   = cur->next;
    cur->next = t;
    q->count++;
}

Task *queue_pop_front(TaskQueue *q)
{
    if (q->head == NULL) return NULL;
    Task *t = q->head;
    q->head = q->head->next;
    t->next = NULL;
    q->count--;
    return t;
}

int queue_is_empty(const TaskQueue *q)
{
    return q->head == NULL;
}

void queue_print(const TaskQueue *q)
{
    printf("  Ready Queue [%d task(s)]: ", q->count);
    for (Task *cur = q->head; cur != NULL; cur = cur->next) {
        printf("T%d(pri=%d,rem=%d) ", cur->id, cur->priority, cur->remaining_time);
    }
    printf("\n");
}

void queue_free_all(TaskQueue *q)
{
    Task *cur = q->head;
    while (cur != NULL) {
        Task *next = cur->next;
        task_destroy(cur);
        cur = next;
    }
    q->head  = NULL;
    q->count = 0;
}
