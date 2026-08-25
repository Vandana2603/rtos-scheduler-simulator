#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

/* Runs a priority + round-robin preemptive scheduling simulation on the
 * given ready queue. 'quantum' is the max ms a task may run before being
 * preempted (round robin behaviour among equal-priority tasks). */
void scheduler_run(TaskQueue *ready_queue, int quantum);

#endif /* SCHEDULER_H */
