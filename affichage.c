#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "jeu.h"



char * IndicesLigne(int * ligne, int m) {

	char * indice = malloc(m*sizeof(char));
	char mot[5]="";
	int i = 0;
	strcpy(indice,"");


	while ((i<m)&&(ligne[i])) {
		sprintf(mot,"%d",ligne[i]);
		strcat(indice,mot);
		strcat(indice," ");
		printf("mot=%s indice=%s\n",mot,indice);
		i++;
	}
	return indice;
}

void Affichagetexte(char * chaine,SDL_Renderer * renderer, SDL_Rect carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int w, int h) {
		
		SDL_Surface	*texte = TTF_RenderText_Shaded(font, chaine, couleur1,couleur2);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,texte);

		carre.x = x;
		carre.y = y;
		carre.w = w;
		carre.h = h;
		SDL_RenderCopy(renderer, texture, NULL, &carre);
		SDL_RenderPresent(renderer);
}

void AffichageIndice();
/*
int main() {
	int n,m;
	int	**	grille = Stocker("test.txt", &n, &m);
	int **	grille_user = InitialiserTableau(n,m);
	int ** grille_user_transp = InitialiserTableau(n,m);
	int ** grille_transp = Transposer(grille,n,m);
	int **	I1= IndiceLignes(n,m,grille_transp);
	int **	I2= IndiceLignes(n,m,grille);
	Afficher(I2,n,m);
	AfficherIndicesLigne(I2[0],m);
	return 0;
}*/
