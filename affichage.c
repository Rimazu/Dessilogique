#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "jeu.h"



char * AfficherIndicesLigne(int * ligne, int m) {

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

void Affichagetexte(char * chaine,SDL_Renderer * renderer,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int width_interface, int height_interface) {

		SDL_Surface	*texte = TTF_RenderText_Shaded(font, chaine, couleur1,couleur2);
		
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,texte);
		int texW = width_interface/4;
		int texH = height_interface/4;
		
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = {x, y, texW, texH };
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
}
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
