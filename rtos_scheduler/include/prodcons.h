#ifndef PRODCONS_H
#define PRODCONS_H

/* Runs a classic bounded-buffer producer/consumer demo using pthreads,
 * a mutex, and condition variables - the core OS synchronisation
 * primitives asked for in the JD (OS fundamentals / Linux). */
void prodcons_run(int num_producers, int num_consumers,
                  int items_per_producer, int buffer_size);

#endif /* PRODCONS_H */
