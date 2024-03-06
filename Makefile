.phony: build run clean valgrind

CC = gcc
CFLAGS = -Wall -Wextra -Werror

build: tema1

tema1: tema1.o banda.h
	$(CC) $(CFLAGS) -o $@ $<

tema1.o: tema1.c
	$(CC) $(CFLAGS) -c $<

run: tema1 tema1.in
	./tema1

valgrind: tema1 tema1.in
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tema1
	
clean:
	rm -f tema1 tema1.o