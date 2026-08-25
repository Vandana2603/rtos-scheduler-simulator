# Mini RTOS Task Scheduler & Producer-Consumer Simulator (C)

A medium-sized C project built to demonstrate the exact skills asked for in an
"Associate (C/C++ Developer) — MCU SW Unit" job description: core C/C++,
data structures, OOP-style design in C, OS fundamentals, Linux, and basic
RTOS/multithreading concepts.

## What it does

The project has two independent demos, both launched from one CLI menu:

1. **Priority + Round-Robin Task Scheduler**
   A ready queue of tasks (each with an id, priority, and CPU burst time) is
   scheduled the way a simple RTOS or OS kernel would: the highest-priority
   task runs first, and if two tasks share a priority they get fair
   round-robin turns via a fixed time quantum. Preempted tasks go back into
   the queue; finished tasks report their turnaround time.

2. **Producer-Consumer with a Bounded Buffer**
   Multiple producer threads and multiple consumer threads share a
   fixed-size circular buffer, protected by a `pthread_mutex_t` and two
   `pthread_cond_t` condition variables (`not_full` / `not_empty`) — the
   textbook OS synchronization pattern.

## Why this maps to the JD

| JD requirement                          | Where it shows up                                   |
|------------------------------------------|------------------------------------------------------|
| Strong C / C++ fundamentals               | Whole project, plain C11                             |
| Data Structures & Algorithms              | Custom priority-sorted linked list (`queue.c`)        |
| OOP concepts                              | `Task` struct as a "class" (TCB), clean module boundaries, header/impl separation |
| Operating System fundamentals             | Scheduling algorithm, task states, turnaround time    |
| Linux environment                         | POSIX threads (`pthread`), Makefile-based build        |
| Embedded Systems / RTOS (preferred)       | Task Control Block, priority scheduling, preemption, time quantum — same concepts used in FreeRTOS/embOS |
| Git / version control (preferred)         | Project is structured so it drops straight into a git repo |
| Debugging / SDLC                          | Built with `-Wall -Wextra`, tested end-to-end below   |

## Project layout

```
rtos_scheduler/
├── include/
│   ├── task.h        # Task Control Block (TCB) + state enum
│   ├── queue.h        # Priority-sorted linked-list ready queue
│   ├── scheduler.h     # Scheduler API
│   └── prodcons.h      # Producer-consumer API
├── src/
│   ├── task.c
│   ├── queue.c
│   ├── scheduler.c
│   ├── prodcons.c
│   └── main.c          # Menu-driven CLI entry point
├── Makefile
└── README.md
```

## Build & run

Requires `gcc` and POSIX threads (present by default on any Linux box).

```bash
make          # builds ./rtos_sim
./rtos_sim    # launches the interactive menu
make clean    # removes build artifacts
```

Menu options:
```
1. Run Priority + Round-Robin Scheduler demo
2. Run Producer-Consumer (threads/mutex/cond) demo
3. Run both
0. Exit
```

## Extending it (good next steps for interview prep)

- Swap the linked-list ready queue for a **binary heap** (classic DSA upgrade).
- Add **task arrival times** so tasks can join mid-simulation (closer to a
  real scheduler tick).
- Add a **semaphore-based** version of the producer-consumer demo alongside
  the mutex/condvar one, to show both primitives.
- Add **unit tests** for `queue.c` (insert/pop ordering) using a simple
  assert-based test harness — ties into "unit testing" in the JD.
- Port the scheduler logic onto real hardware (e.g. an STM32 + FreeRTOS) to
  directly demonstrate the "Embedded Systems / RTOS" preferred skill.
