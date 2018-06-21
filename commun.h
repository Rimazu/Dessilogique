#ifndef COMMUN_H
#define COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define NB_COUPS_TOTAL 50

typedef struct {
	int i;			/* coordonnées dans la grille du coup*/
	int j;
	int etatcase;   /* etatcase contient 0 (case pas coloriée), 1 (case coloriée) ou 2 (case "marquée")*/
} coup_t;

typedef struct {
	int sommet;		/* Position de la case et son état avant le dernier coup joué dans base */
	coup_t * base;	/* Liste qui stocke les coups joués */
} Tcoup_t;


Tcoup_t * InitialisationCoup(int * PCompteurCoups);		/* Initialise Tcoup-t */

/* Met à jour Tabcoup en fonction du dernier coup joué */
Tcoup_t * MajCoup(Tcoup_t * TabCoup, int i, int j, int etatcase,int * PCompteurCoups) ;

/* Permet de supprimer le dernier coup joué de la grille utilisateur et actualiser l'affichage de la grille */
Tcoup_t * AnnulationCoup(Tcoup_t * TabCoup,int * PCompteurCoups, int ** grille_user, int ** grille_user_transp,SDL_Renderer * renderer, SDL_Rect Carre,int width_interface,int width_grille, int height_interface, int height_grille,int m,int n);

void LiberationCoups(Tcoup_t * TabCoup);			/* Libère la mémoire allouée pour la structure */

#endif

