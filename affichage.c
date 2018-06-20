#include "affichage.h"

void AffichageJeu(SDL_Renderer * renderer, SDL_Rect Carre, SDL_Rect * Bouton,SDL_Rect * SaveBouton,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int ** IndiceLignes,int ** IndiceColonnes,int width, int height, int width_grille, int width_interface, int height_grille,int height_interface,int ** grille_user, int m, int n, int essai, char * textEssai, char * buffer, SDL_Surface * texte, SDL_Texture * texture)
{


	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_RenderClear(renderer);

	AffichageGrille(renderer,Carre,width,height,width_grille,width_interface,height_grille,height_interface,grille_user, m, n);

	AffichageBouton(renderer,Bouton,width_interface,height_interface, couleur1,font, texte, texture);
	AffichageSave(renderer,SaveBouton,width_interface,height_interface,couleur1,font, texte, texture);


	/* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
	sprintf(buffer,"%d",essai);
	strcpy(textEssai,"Echecs : ");
	strcat(textEssai, buffer);
	Affichagetexte(texte,texture,textEssai,renderer,Carre,font,couleur1,couleur2,Bouton->x,Bouton->y+Bouton->h,Bouton->w,Bouton->h);

	/*Affichage des indices de la grille*/
	AffichageIndiceLignes(renderer,Carre,font,couleur1,couleur2,width,height,IndiceLignes,m,n,texte,texture);
	AffichageIndiceColonnes(renderer,Carre,font,couleur1,couleur2,width,height,IndiceColonnes,m,n,texte,texture);
}

void AffichageMenu(SDL_Renderer * renderer,SDL_Rect Carre,SDL_Rect * LoadBouton,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2, int width, int height, SDL_Surface * texte, SDL_Texture * texture)
{
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor( renderer, 50, 180, 50, 255 );
	/*SDL_RenderDrawLine(renderer, 0, height/5, width, 0);*/
	Carre.x = 0;
	Carre.y = height/5;
	Carre.w = width;
	Carre.h = height*4/5;
	SDL_RenderFillRect(renderer,&Carre);

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderDrawLine(renderer, width/3, height/5, width/3, height);
	SDL_RenderDrawLine(renderer, 2*width/3, height/5, 2*width/3, height);
	Affichagetexte(texte,texture,"Dessilogique",renderer,Carre,font,couleur1,couleur2,width/7,0,width*3/5,height/6);
	couleur2.r = 50;
	couleur2.g = 180;
	couleur2.b = 50;
	Affichagetexte(texte,texture,"Grille 1",renderer,Carre,font,couleur1,couleur2,width*0.1/3,height*3*0.8/5,width*0.8/3,2*height*3*0.2/5);
	Affichagetexte(texte,texture,"Grille 2",renderer,Carre,font,couleur1,couleur2,width*1.1/3,height*3*0.8/5,width*0.8/3,2*height*3*0.2/5);
	Affichagetexte(texte,texture,"Grille 3",renderer,Carre,font,couleur1,couleur2,width*2.1/3,height*3*0.8/5,width*0.8/3,2*height*3*0.2/5);
	SDL_RenderPresent(renderer);

	AffichageLoad(renderer,LoadBouton,width,height,couleur1,font,texte,texture);

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

void Affichagetexte(SDL_Surface * texte,SDL_Texture * texture,char * chaine,SDL_Renderer * renderer, SDL_Rect carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int w, int h) {

	texte = TTF_RenderText_Shaded(font, chaine, couleur1,couleur2);
	texture = SDL_CreateTextureFromSurface(renderer,texte);

	carre.x = x;
	carre.y = y;
	carre.w = w;
	carre.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &carre);
	SDL_RenderPresent(renderer);
}

void AffichageIndice1Ligne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * ligne, int m, int n, int NumLigne, SDL_Surface * texte, SDL_Texture * texture) {
	char	indice[3]="";
	int		i = m - 1,
			x = 0.35 * width,
			y = 0.35 * height + 0.65 * height * NumLigne / n,
			pas = 0.7 * 2 * 0.35 * width / m;

	while (i >= 0) {
		if (ligne[i] != 0) {
			sprintf(indice,"%d",ligne[i]);
			x = x - pas;
			Affichagetexte(texte,texture,indice,renderer,Carre,font,couleur1,couleur2,x,y,pas,pas);
		}
		i--;
	}
}

void AffichageIndice1Colonne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * colonne, int m, int n, int NumColonne, SDL_Surface * texte, SDL_Texture * texture) {
	char	indice[3]="";
	int		i = n - 1,
			x = 0.35 * width + 0.65 * width * NumColonne / m,
			y = 0.35 * height,
			pas = 0.7 * 2 * 0.35 * height / n;

	while (i >= 0) {
		if (colonne[i] != 0) {
			sprintf(indice,"%d",colonne[i]);
			y = y - pas;
			Affichagetexte(texte,texture,indice,renderer,Carre,font,couleur1,couleur2,x,y,pas,pas);
		}
		i--;
	}
}


void AffichageIndiceLignes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceLignes, int m, int n, SDL_Surface * texte, SDL_Texture * texture) {
	int i;

	for (i=0; i<n; i++) {
		AffichageIndice1Ligne(renderer,Carre,font,couleur1,couleur2,width,height,IndiceLignes[i],m,n,i,texte,texture);
	}
}

void AffichageIndiceColonnes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceColonnes, int m, int n, SDL_Surface * texte, SDL_Texture * texture) {
	int i;

	for (i=0; i<m; i++) {
		AffichageIndice1Colonne(renderer,Carre,font,couleur1,couleur2,width,height,IndiceColonnes[i],m,n,i,texte,texture);
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

void AffichageBouton(SDL_Renderer * renderer, SDL_Rect * Bouton, int width_interface, int height_interface, SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture)
{
	Bouton->x = width_interface/6;
	Bouton->w = width_interface/3;
	Bouton->y = height_interface/5;
	Bouton->h = height_interface/3;
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, Bouton);

	texte = TTF_RenderText_Blended(font, "Test", couleur1);
	texture = SDL_CreateTextureFromSurface(renderer,texte);
	SDL_RenderCopy(renderer, texture, NULL, Bouton);
	SDL_RenderPresent(renderer);
}

void AffichageSave(SDL_Renderer * renderer, SDL_Rect * SaveBouton, int width_interface, int height_interface, SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture)
{

	SaveBouton->x = 13*width_interface/24;
	SaveBouton->w = width_interface/3;
	SaveBouton->y = height_interface/5;
	SaveBouton->h = height_interface/3;
	SDL_SetRenderDrawColor(renderer, 0, 200, 50, 255);
	SDL_RenderFillRect(renderer, SaveBouton);

	texte = TTF_RenderText_Blended(font, "Save", couleur1);
	texture = SDL_CreateTextureFromSurface(renderer,texte);
	SDL_RenderCopy(renderer, texture, NULL, SaveBouton);
	SDL_RenderPresent(renderer);
}

void AffichageLoad(SDL_Renderer * renderer, SDL_Rect * LoadBouton, int width, int height, SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture)
{

	LoadBouton->x = 4*width/5;
	LoadBouton->w = width/5;
	LoadBouton->y = 0;
	LoadBouton->h = height/5;
	SDL_SetRenderDrawColor(renderer, 80, 80, 150, 255);
	SDL_RenderFillRect(renderer, LoadBouton);

	texte = TTF_RenderText_Blended(font, "Load", couleur1);
	texture = SDL_CreateTextureFromSurface(renderer,texte);
	SDL_RenderCopy(renderer, texture, NULL, LoadBouton);
	SDL_RenderPresent(renderer);
}


void Coloriage(SDL_Event event, SDL_Renderer * renderer, SDL_Rect Carre, int width_interface,int width_grille, int height_interface, int height_grille,int m,int n, int ** grille_user, int ** grille_user_transp,Tcoup_t * TabCoup)
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
	MajCoup(TabCoup,iy,ix,grille_user[iy][ix]); /*grille_user[iy][ix] signifie l'état de la case*/
	
	grille_user_transp[ix][iy] = grille_user[iy][ix];
	SDL_RenderFillRect(renderer, &Carre);
	SDL_RenderPresent(renderer);
}
