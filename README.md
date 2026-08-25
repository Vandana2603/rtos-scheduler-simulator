# Mini RTOS Scheduler Simulator

A lightweight C-based simulation of core Real-Time Operating System (RTOS) concepts, including priority-based scheduling, Round-Robin scheduling, task preemption, and multithreaded producer-consumer synchronization.

## Features

- Priority-based task scheduling
- Round-Robin scheduling for tasks with the same priority
- Configurable time quantum
- Task preemption and termination simulation
- Ready queue management
- Task turnaround-time tracking
- Producer-Consumer synchronization
- POSIX threads (`pthread`)
- Mutex and condition variables
- Linux/WSL compatible
- Makefile-based build system

## Technologies

- **C**
- **GCC**
- **POSIX Threads (pthread)**
- **Linux / WSL**
- **Make**
- Data Structures
- Operating System concepts
- RTOS scheduling concepts

## Project Structure

```text
rtos-scheduler-simulator/
│
├── include/
│   ├── task.h
│   ├── queue.h
│   ├── scheduler.h
│   └── prodcons.h
│
├── src/
│   ├── main.c
│   ├── task.c
│   ├── queue.c
│   ├── scheduler.c
│   └── prodcons.c
│
├── Makefile
├── README.md
└── .gitignore
