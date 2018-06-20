#ifndef COMMUN
#define COMMUN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define NB_COUPS_TOTAL 50

typedef struct {
	int i;
	int j;
	int etat;
} coup_t;

typedef struct {
	int sommet;
	coup_t * base;
} Tcoup_t;


#endif
