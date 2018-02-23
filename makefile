#!/bin/makefile

CC=gcc

CFLAGS= -g -Wall -Wextra 

LDFLAGS= -lm -lX11

OBJ= 

EXEC= dessilogique

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< $(CFLAGS) 


clean:
	rm *.o

cleaner: clean
	rm $(EXEC)
