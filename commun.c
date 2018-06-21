#include "commun.h"

Tcoup_t * InitialisationCoup(int * PCompteurCoups) {
	Tcoup_t * TabCoup = (Tcoup_t *)malloc(sizeof(Tcoup_t));
	
	*PCompteurCoups = 0;
	TabCoup->sommet = -1;
	TabCoup->base = (coup_t *)malloc(NB_COUPS_TOTAL*sizeof(coup_t));
	
	return TabCoup;
}

Tcoup_t * MajCoup(Tcoup_t * TabCoup, int i, int j, int etatcase, int * PCompteurCoups) {
	coup_t coup;
	
	coup.i = i;
	coup.j = j;
	coup.etatcase = etatcase; /* Stockage du coup dans sa variable associée */
	
	TabCoup->sommet++;			/* on incrémente le sommet, qui signifie l'indice du dernier coup joué */
	if (TabCoup->sommet >= NB_COUPS_TOTAL)
	{
		TabCoup->sommet = 0;	/* Si on a dépassé la fin de la liste, on revient au début */
	}
	if (*PCompteurCoups < NB_COUPS_TOTAL)
	{
		(*PCompteurCoups)++;	/* On incrémente le nombre de coups stockés */
	}

	(TabCoup->base)[TabCoup->sommet] = coup; /* ajout du coup dans la liste */
	
	return(TabCoup);
}

Tcoup_t * AnnulationCoup(Tcoup_t * TabCoup,int * PCompteurCoups, int ** grille_user,int ** grille_user_transp, SDL_Renderer * renderer, SDL_Rect Carre,int width_interface,int width_grille, int height_interface, int height_grille,int m,int n) {
	int etatcase,i,j; 
	
	if (*PCompteurCoups > 0) {
		etatcase = (TabCoup->base)[TabCoup->sommet].etatcase;
		i = (TabCoup->base)[TabCoup->sommet].i, /* On prend l'état de la case avant le dernier coup joué */
		j = (TabCoup->base)[TabCoup->sommet].j;
		(*PCompteurCoups)--;					/* On décrémente le nombre de coups stockés */
		
		if (--TabCoup->sommet < 0) {			/* On décrémente le sommet */
			TabCoup->sommet = NB_COUPS_TOTAL-1; /* Si on dépasse le début de la liste, on revient à la fin*/
		}
		
		grille_user[i][j] = etatcase;
		grille_user_transp[j][i] = etatcase; 	/* On change les grilles du joueur en "annulant" son dernier coup */
	
		Carre.x = j*(width_grille/m)+width_interface;  /* On définit la zone à colorier */
		Carre.w = width_grille/m * 0.9;
		Carre.y = i*(height_grille/n)+height_interface;
		Carre.h = height_grille/n * 0.9;
		
		/* On colorie la case graphique en accordance avec l'annulation */
		
		if (etatcase == 0)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else
		{
			if (etatcase == 1)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
		}
		
		SDL_RenderFillRect(renderer, &Carre);
		SDL_RenderPresent(renderer);
	}
	
	return(TabCoup);
}
	
void LiberationCoups(Tcoup_t * TabCoup) {
	
	if (TabCoup) {
		if (TabCoup->base) {
			free(TabCoup->base);
		}
		free(TabCoup);
	}
}
