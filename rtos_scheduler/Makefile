CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -D_DEFAULT_SOURCE -g -Iinclude
LDFLAGS = -lpthread
SRC     = src/task.c src/queue.c src/scheduler.c src/prodcons.c src/main.c
OBJ     = $(SRC:.c=.o)
TARGET  = rtos_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
