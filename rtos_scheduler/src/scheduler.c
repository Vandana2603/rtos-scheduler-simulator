#include <stdio.h>
#include "../include/scheduler.h"

/* Priority + Round-Robin preemptive scheduler simulation.
 *
 * Algorithm:
 *   1. Pop the highest-priority (and, among ties, longest-waiting) task.
 *   2. Run it for min(quantum, remaining_time) simulated milliseconds.
 *   3. If it still has work left, re-insert it into the sorted queue
 *      (this naturally lands it after any equal-priority tasks that
 *      arrived first -> classic round robin), otherwise mark it
 *      TERMINATED and record its completion time / turnaround time.
 */
void scheduler_run(TaskQueue *ready_queue, int quantum)
{
    int current_time = 0;
    int completed     = 0;
    int total_tasks   = ready_queue->count;

    printf("\n=== Starting Scheduler (quantum = %dms) ===\n", quantum);

    while (!queue_is_empty(ready_queue)) {
        Task *t = queue_pop_front(ready_queue);
        t->state = TASK_RUNNING;

        int run_time = (t->remaining_time < quantum) ? t->remaining_time : quantum;

        printf("[t=%4dms] Running Task %d (priority %d) for %dms\n",
               current_time, t->id, t->priority, run_time);

        current_time      += run_time;
        t->remaining_time -= run_time;

        if (t->remaining_time > 0) {
            t->state = TASK_READY;
            printf("           -> Task %d preempted, %dms remaining\n",
                   t->id, t->remaining_time);
            queue_push_sorted(ready_queue, t);
        } else {
            t->state           = TASK_TERMINATED;
            t->completion_time = current_time;
            completed++;
            int turnaround = t->completion_time - t->arrival_time;
            printf("           -> Task %d TERMINATED at t=%dms (turnaround=%dms)\n",
                   t->id, t->completion_time, turnaround);
            task_destroy(t);
        }
        queue_print(ready_queue);
    }

    printf("=== Scheduler finished: %d/%d tasks completed at t=%dms ===\n\n",
           completed, total_tasks, current_time);
}
