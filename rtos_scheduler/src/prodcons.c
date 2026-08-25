#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../include/prodcons.h"

/* Shared state for the bounded-buffer producer/consumer problem.
 * Demonstrates: mutex locking, condition variables, thread creation/join -
 * the "OS fundamentals" and "Linux environment" pieces of the JD. */
typedef struct {
    int  *buffer;
    int   capacity;
    int   count;      /* items currently in buffer */
    int   in;         /* next write index */
    int   out;        /* next read index */
    int   items_per_producer;
    int   producers_done;
    int   total_producers;
    pthread_mutex_t lock;
    pthread_cond_t  not_full;
    pthread_cond_t  not_empty;
} SharedBuffer;

typedef struct {
    int id;
    SharedBuffer *sb;
} WorkerArg;

static void buffer_init(SharedBuffer *sb, int capacity, int items_per_producer, int total_producers)
{
    sb->buffer             = (int *)malloc(sizeof(int) * capacity);
    sb->capacity           = capacity;
    sb->count              = 0;
    sb->in                 = 0;
    sb->out                = 0;
    sb->items_per_producer = items_per_producer;
    sb->producers_done     = 0;
    sb->total_producers    = total_producers;
    pthread_mutex_init(&sb->lock, NULL);
    pthread_cond_init(&sb->not_full, NULL);
    pthread_cond_init(&sb->not_empty, NULL);
}

static void buffer_destroy(SharedBuffer *sb)
{
    free(sb->buffer);
    pthread_mutex_destroy(&sb->lock);
    pthread_cond_destroy(&sb->not_full);
    pthread_cond_destroy(&sb->not_empty);
}

static void *producer_thread(void *arg)
{
    WorkerArg *w = (WorkerArg *)arg;
    SharedBuffer *sb = w->sb;

    for (int i = 0; i < sb->items_per_producer; i++) {
        int item = w->id * 1000 + i;

        pthread_mutex_lock(&sb->lock);
        while (sb->count == sb->capacity) {
            pthread_cond_wait(&sb->not_full, &sb->lock);
        }
        sb->buffer[sb->in] = item;
        sb->in = (sb->in + 1) % sb->capacity;
        sb->count++;
        printf("  [Producer %d] produced item %d (buffer count=%d)\n", w->id, item, sb->count);
        pthread_cond_signal(&sb->not_empty);
        pthread_mutex_unlock(&sb->lock);

        usleep(2000); /* simulate work */
    }

    pthread_mutex_lock(&sb->lock);
    sb->producers_done++;
    if (sb->producers_done == sb->total_producers) {
        /* wake up any consumers still waiting so they can see "all done" */
        pthread_cond_broadcast(&sb->not_empty);
    }
    pthread_mutex_unlock(&sb->lock);

    free(w);
    return NULL;
}

static void *consumer_thread(void *arg)
{
    WorkerArg *w = (WorkerArg *)arg;
    SharedBuffer *sb = w->sb;

    for (;;) {
        pthread_mutex_lock(&sb->lock);
        while (sb->count == 0 && sb->producers_done < sb->total_producers) {
            pthread_cond_wait(&sb->not_empty, &sb->lock);
        }
        if (sb->count == 0 && sb->producers_done == sb->total_producers) {
            pthread_mutex_unlock(&sb->lock);
            break; /* nothing left to consume, all producers finished */
        }
        int item = sb->buffer[sb->out];
        sb->out = (sb->out + 1) % sb->capacity;
        sb->count--;
        printf("    [Consumer %d] consumed item %d (buffer count=%d)\n", w->id, item, sb->count);
        pthread_cond_signal(&sb->not_full);
        pthread_mutex_unlock(&sb->lock);

        usleep(3000); /* simulate work */
    }

    free(w);
    return NULL;
}

void prodcons_run(int num_producers, int num_consumers,
                  int items_per_producer, int buffer_size)
{
    SharedBuffer sb;
    buffer_init(&sb, buffer_size, items_per_producer, num_producers);

    pthread_t *producers = malloc(sizeof(pthread_t) * num_producers);
    pthread_t *consumers = malloc(sizeof(pthread_t) * num_consumers);

    printf("\n=== Starting Producer-Consumer Demo ===\n");
    printf("Producers=%d Consumers=%d BufferSize=%d ItemsPerProducer=%d\n\n",
           num_producers, num_consumers, buffer_size, items_per_producer);

    for (int i = 0; i < num_producers; i++) {
        WorkerArg *w = malloc(sizeof(WorkerArg));
        w->id = i + 1;
        w->sb = &sb;
        pthread_create(&producers[i], NULL, producer_thread, w);
    }
    for (int i = 0; i < num_consumers; i++) {
        WorkerArg *w = malloc(sizeof(WorkerArg));
        w->id = i + 1;
        w->sb = &sb;
        pthread_create(&consumers[i], NULL, consumer_thread, w);
    }

    for (int i = 0; i < num_producers; i++) pthread_join(producers[i], NULL);
    for (int i = 0; i < num_consumers; i++) pthread_join(consumers[i], NULL);

    free(producers);
    free(consumers);
    buffer_destroy(&sb);

    printf("=== Producer-Consumer Demo finished ===\n\n");
}
