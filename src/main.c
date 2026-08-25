#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"
#include "../include/queue.h"
#include "../include/scheduler.h"
#include "../include/prodcons.h"

static void run_scheduler_demo(void)
{
    TaskQueue rq;
    queue_init(&rq);

    /* id, priority (0 = highest), burst_time(ms), arrival_time */
    queue_push_sorted(&rq, task_create(1, 2, 12, 0));
    queue_push_sorted(&rq, task_create(2, 0, 6,  0));
    queue_push_sorted(&rq, task_create(3, 1, 9,  0));
    queue_push_sorted(&rq, task_create(4, 0, 4,  0));
    queue_push_sorted(&rq, task_create(5, 2, 5,  0));

    printf("Initial state:\n");
    queue_print(&rq);

    scheduler_run(&rq, 4 /* time quantum in ms */);
}

static void run_prodcons_demo(void)
{
    prodcons_run(2 /*producers*/, 3 /*consumers*/, 5 /*items each*/, 4 /*buffer size*/);
}

static void print_menu(void)
{
    printf("=====================================\n");
    printf(" Mini RTOS Task Scheduler Simulator\n");
    printf("=====================================\n");
    printf(" 1. Run Priority + Round-Robin Scheduler demo\n");
    printf(" 2. Run Producer-Consumer (threads/mutex/cond) demo\n");
    printf(" 3. Run both\n");
    printf(" 0. Exit\n");
    printf("-------------------------------------\n");
    printf("Choice: ");
}

int main(void)
{
    int choice;

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return EXIT_FAILURE;
        }

        switch (choice) {
            case 1: run_scheduler_demo(); break;
            case 2: run_prodcons_demo();  break;
            case 3: run_scheduler_demo(); run_prodcons_demo(); break;
            case 0: printf("Exiting.\n"); return EXIT_SUCCESS;
            default: printf("Unknown option.\n"); break;
        }
    }

    return EXIT_SUCCESS;
}
