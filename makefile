#!/bin/makefile

CC=gcc

CFLAGS= -g -Wall -Wextra 

OBJ= prog.o

EXEC=prog

$(EXEC): $(OBJ)
	$(CC) $^ -o $@

prog.o: prog.h
	$(CC) -c prog.c $(CFLAGS)

clean:
	rm *.o

cleaner: clean
	rm $(EXEC)
