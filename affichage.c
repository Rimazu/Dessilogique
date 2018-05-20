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

void AffichageIndice1Ligne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * ligne, int m, int n, int NumLigne) {
	char	indice[3]="";
	int		i = m - 1,
			x = 0.35 * width,
			y = 0.35 * height + 0.65 * height * NumLigne / n,
			pas = 0.7 * 2 * 0.35 * width / m;
	
	while (i >= 0) {
		if (ligne[i] != 0) {
			sprintf(indice,"%d",ligne[i]);
			x = x - pas;
			Affichagetexte(indice,renderer,Carre,font,couleur1,couleur2,x,y,pas,pas);
		}
		i--;
	}
}

void AffichageIndice1Colonne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * colonne, int m, int n, int NumColonne) {
	char	indice[3]="";
	int		i = n - 1,
			x = 0.35 * width + 0.65 * width * NumColonne / m,
			y = 0.35 * height,
			pas = 0.7 * 2 * 0.35 * height / n;

	while (i >= 0) {
		if (colonne[i] != 0) {
			sprintf(indice,"%d",colonne[i]);
			y = y - pas;
			Affichagetexte(indice,renderer,Carre,font,couleur1,couleur2,x,y,pas,pas);
		}
		i--;
	}
}


void AffichageIndiceLignes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceLignes, int m, int n) {
	int i;
	
	for (i=0; i<n; i++) {
		AffichageIndice1Ligne(renderer,Carre,font,couleur1,couleur2,width,height,IndiceLignes[i],m,n,i);
	}
}

void AffichageIndiceColonnes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceColonnes, int m, int n) {
	int i;
	
	for (i=0; i<m; i++) {
		AffichageIndice1Colonne(renderer,Carre,font,couleur1,couleur2,width,height,IndiceColonnes[i],m,n,i);
	}
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
