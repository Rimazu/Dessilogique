
#include <string.h>
#include "affichage.h"
#include "jeu.h"



void AffichageJeu(SDL_Renderer * renderer, SDL_Rect Carre, SDL_Rect * Bouton,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int ** IndiceLignes,int ** IndiceColonnes,int width, int height, int width_grille, int width_interface, int height_grille,int height_interface,int ** grille_user, int m, int n, int essai, char * textEssai, char * buffer)
{


	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_RenderClear(renderer);

	AffichageGrille(renderer,Carre,width,height,width_grille,width_interface,height_grille,height_interface,grille_user, m, n);

	AffichageBouton(renderer,Bouton,width_interface,height_interface);

	/* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
	sprintf(buffer,"%d",essai);
	strcpy(textEssai,"Echecs : ");
	strcat(textEssai, buffer);
	Affichagetexte(textEssai,renderer,Carre,font,couleur1,couleur2,Bouton->x,Bouton->y+Bouton->h,Bouton->w,Bouton->h);

	/*Affichage des indices de la grille*/
	AffichageIndiceLignes(renderer,Carre,font,couleur1,couleur2,width,height,IndiceLignes,m,n);
	AffichageIndiceColonnes(renderer,Carre,font,couleur1,couleur2,width,height,IndiceColonnes,m,n);
}

void AffichageMenu(SDL_Renderer * renderer, int width, int height)
{
	SDL_SetRenderDrawColor( renderer, 50, 180, 50, 255 );
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderDrawLine(renderer, width/3, 0, width/3, height);
	SDL_RenderDrawLine(renderer, 2*width/3, 0, 2*width/3, height);
	SDL_RenderPresent(renderer);
}


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


void AffichageGrille(SDL_Renderer * renderer, SDL_Rect Carre,int width, int height, int width_grille, int width_interface, int height_grille,int height_interface,int ** grille_user, int m, int n)
{
	int i,j,ix,iy;

	for (i=height_interface;i<=(height-height_grille/n);i=i+height_grille/n) {
		for (j=width_interface;j<=(width-width_grille/m);j=j+width_grille/m) {

			ix = (j-width_interface)/(width_grille/m);
			iy = (i-height_interface)/(height_grille/n);


			Carre.x = j;
			Carre.w = width_grille/m * 0.9;
			Carre.y = i;
			Carre.h = height_grille/n * 0.9;
			SDL_SetRenderDrawColor(renderer,(grille_user[iy][ix] == -1)? 255:0, (grille_user[iy][ix] == 0)? 0:255, (grille_user[iy][ix] == 1)? 0:255, 255);
			SDL_RenderFillRect(renderer, &Carre);
		}

	}
}

void AffichageBouton(SDL_Renderer * renderer, SDL_Rect * Bouton, int width_interface, int height_interface)
{
	Bouton->x = width_interface/5;
	Bouton->w = width_interface/3;
	Bouton->y = height_interface/5;
	Bouton->h = height_interface/3;
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, Bouton);
}

void Coloriage(SDL_Event event, SDL_Renderer * renderer, SDL_Rect Carre, int width_interface,int width_grille, int height_interface, int height_grille,int m,int n, int ** grille_user, int ** grille_user_transp)
{
	int ix = (int)(event.button.x-width_interface)/(width_grille/m);
	int iy = (int)(event.button.y - height_interface)/(height_grille/n);
	Carre.x = ix*(width_grille/m)+width_interface;
	printf("%d %d %d \n", ix, iy, grille_user[iy][ix]);
	printf("%d %d \n",Carre.x, ix);
	Carre.w = width_grille/m * 0.9;
	Carre.y = iy*(height_grille/n)+height_interface;
	Carre.h = height_grille/n * 0.9;

	if (event.button.button == SDL_BUTTON_LEFT) {
		if (grille_user[iy][ix] == 1) {
			grille_user[iy][ix] = 0;
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			grille_user[iy][ix] = 1;
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
	}
	else {
		if (grille_user[iy][ix] == -1) {
			grille_user[iy][ix] = 0;
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			grille_user[iy][ix] = -1;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
	}
	grille_user_transp[ix][iy] = grille_user[iy][ix];
	SDL_RenderFillRect(renderer, &Carre);
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
