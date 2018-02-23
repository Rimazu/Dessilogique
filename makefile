#!/bin/makefile

CC=gcc

CFLAGS= -g -Wall -Wextra -ansi -pedantic -Wcomment -Wformat 

LDFLAGS= -lm -lX11 -lSDL2 -lSDL2_ttf -lSDL2_image

OBJ= *.o

EXEC= dessilogique

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< $(CFLAGS) 


clean:
	rm *.o

cleaner: clean
	rm $(EXEC)
