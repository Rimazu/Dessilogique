#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"
#include "affichage.h"

int main() {

	int		n,m,i,j,ix,iy,succes=0;
	int 	essai=0;
	char textEssai[80];
	char buffer[3];

	int	**	grille = Stocker("test.txt", &n, &m);
	int **	grille_user = InitialiserTableau(n,m);
	int ** grille_user_transp = InitialiserTableau(m,n);
	int ** grille_transp = Transposer(grille,n,m);
	int **	I1= IndiceLignes(m,n,grille_transp);
	int **	I2= IndiceLignes(n,m,grille);

	int width = 80*m;
	int height = 80*n;
	int width_interface = 0.35 * width;
	int height_interface = 0.35 * height;
	int width_grille = 0.65 * width;
	int height_grille = 0.65 * height;

	int 	run = 1;
	int erreur = 0;

	SDL_Renderer * renderer;
	SDL_Rect Carre;
	SDL_Rect Bouton;


	TTF_Font * font;
	SDL_Surface	*texte=NULL;
	SDL_Texture * texture=NULL;
	SDL_Color couleurNoire = {0,0,0,0};
	SDL_Color couleurRouge = {255,0,0,0};

	/* variable d'initialisation de SDL_image */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	/* variable liee a la fenetre */
	SDL_Window * window;
	/* variables liees a la capture d'evenement */
	SDL_Event event;


	printf("Variables initialisées !\n");



	/* initialisation de la SDL2 */
	if(SDL_Init(SDL_INIT_VIDEO) == 1){
			fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
			return EXIT_FAILURE;
	}

	/* initialisation de SDL_ttf */
	if (TTF_Init() != 0){
			fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
			SDL_Quit();
			return EXIT_FAILURE;
	}

	/* initialisation de SDL_image */
	if((IMG_Init(flags)&flags) != flags){
			printf("IMG_Init: Failed to init required jpg and png support!\n");
			printf("IMG_Init: %s\n", IMG_GetError());
			TTF_Quit();
			SDL_Quit();
			return EXIT_FAILURE;
	}

	/* ouverture de la fenetre */
	window = SDL_CreateWindow("Dessilogique",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														width,height,
														SDL_WINDOW_RESIZABLE);

	if(!window){
		fprintf(stderr,"Erreur de creation de la fenetre : %s\n", SDL_GetError());
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* initialisation du renderer */
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(!renderer){
		fprintf(stderr,"Erreur de creation du renderer\n");
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	printf("SDL initialisée !\n");

	/*initialisation de la police*/
	font = TTF_OpenFont("arial.ttf",20);

	printf("Evenements initialisés !\n");


	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_RenderClear(renderer);


	for (i=height_interface;i<=(height-height_grille/n);i=i+height_grille/n) {
		for (j=width_interface;j<=(width-width_grille/m);j=j+width_grille/m) {

			Carre.x = j;
			Carre.w = width_grille/m * 0.9;
			Carre.y = i;
			Carre.h = height_grille/n * 0.9;
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &Carre);
		}

	}

	Bouton.x = width_interface/5;
	Bouton.w = width_interface/3;
	Bouton.y = height_interface/5;
	Bouton.h = height_interface/3;
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Bouton);

  /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
	sprintf(buffer,"%d",essai);
	strcpy(textEssai,"Echecs : ");
	strcat(textEssai, buffer);

	Affichagetexte(textEssai,renderer,Carre,font,couleurNoire,couleurRouge,Bouton.x,Bouton.y+Bouton.h,Bouton.w,Bouton.h);
	while (run) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							run = 0;
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = event.window.data1;
							height = event.window.data2;

							width_interface = 0.35 * width;
							height_interface = 0.35 * height;
							width_grille = 0.65 * width;
							height_grille = 0.65 * height;
							font = TTF_OpenFont("arial.ttf",20*width*height/(80*n*80*m));
							SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
							SDL_RenderClear(renderer);
							for (i=height_interface;i<=(height-height_grille/n);i=i+height_grille/n) {
								for (j=width_interface;j<=(width-width_grille/m);j=j+width_grille/m) {

									ix = (j-width_interface)/(width_grille/m);
									iy = (i-height_interface)/(height_grille/n);

									Carre.x = j;
									Carre.w = width_grille/m * 0.9;
									Carre.y = i;
									Carre.h = height_grille/n * 0.9;

									SDL_SetRenderDrawColor(renderer, (grille_user[iy][ix] == -1)? 255:0, (grille_user[iy][ix] == 0)? 0:255, (grille_user[iy][ix] == 1)? 0:255, 255);
									SDL_RenderFillRect(renderer, &Carre);
								}

							}
							Bouton.x = width_interface/5;
							Bouton.w = width_interface/3;
							Bouton.y = height_interface/5;
							Bouton.h = height_interface/3;
							SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
							SDL_RenderFillRect(renderer, &Bouton);

							sprintf(buffer,"%d",essai);
							strcpy(textEssai,"Echecs : ");
							strcat(textEssai, buffer);
							texte = TTF_RenderText_Blended(font, textEssai, couleurNoire);
							texture = SDL_CreateTextureFromSurface(renderer,texte);

							Carre.x = Bouton.x;
							Carre.y = Bouton.y+Bouton.h;
							Carre.w = Bouton.w;
							Carre.h = Bouton.h;

							SDL_RenderCopy(renderer, texture, NULL, &Carre);
							SDL_RenderPresent(renderer);
							printf("Size : %d%d\n", width, height);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (succes) {
						run = 0;
					}
					else
						{
						if (((event.button.x-width_interface)%(width_grille/m)<=0.9*width_grille/m)&&((event.button.y-height_interface)%(height_grille/n)<=0.9*height_grille/n)&&(event.button.x<=width - (0.1 * width_grille/m))&&(event.button.y <= height - (0.1 * height_grille/n))&&(event.button.x>=width_interface)&&(event.button.y>=height_interface)) {
							ix = (int)(event.button.x-width_interface)/(width_grille/m);
							iy = (int)(event.button.y - height_interface)/(height_grille/n);
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
						if ((event.button.x >=Bouton.x)&&(event.button.x <= Bouton.x + Bouton.w)&&(event.button.y >=Bouton.y)&&(event.button.y <=Bouton.y + Bouton.h)) {
								erreur = VerificationSucces(n,m,I1,I2,grille_user,grille_user_transp);
				        if (erreur==0) {

									succes = 1;

									TTF_SetFontStyle(font, TTF_STYLE_BOLD);
									font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
			
									Affichagetexte("Success",renderer,Carre,font,couleurNoire,couleurRouge,width/4,height/4,width/2,height/2);

								}
						else {
									essai++;
									sprintf(buffer,"%d",essai);
									strcpy(textEssai,"Echecs : ");
									strcat(textEssai, buffer);
									Affichagetexte(textEssai,renderer,Carre,font,couleurNoire,couleurRouge,Bouton.x,Bouton.y+Bouton.h,Bouton.w,Bouton.h);
						}

	        	}
					}
					break;
				case SDL_QUIT :
					printf("on quitte\n");
					run = 0;
			}
		}
	}
	if(renderer)
		SDL_DestroyRenderer(renderer);

	/* on libere la fenetre */
	SDL_DestroyWindow(window);
	/* fermeture de SDL_image, SDL_ttf et SDL2 */
	IMG_Quit();
	TTF_CloseFont(font);
	SDL_FreeSurface(texte);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
