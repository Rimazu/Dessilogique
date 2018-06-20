#ifndef COMMUN_H
#define COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define NB_COUPS_TOTAL 50

typedef struct {
	int i;
	int j;
	int etatcase;
} coup_t;

typedef struct {
	int sommet;
	coup_t * base;
} Tcoup_t;


Tcoup_t * InitialiserCoup(int * PCompteurCoups);

Tcoup_t * MajCoup(Tcoup_t * TabCoup, int i, int j, int etatcase,int * PCompteurCoups) ;

Tcoup_t * AnnulerCoup(Tcoup_t * TabCoup,int * PCompteurCoups, int ** grille_user, int ** grille_user_transp,SDL_Renderer * renderer, SDL_Rect Carre,int width_interface,int width_grille, int height_interface, int height_grille,int m,int n);

void LibererCoups(Tcoup_t * TabCoup);

#endif

