#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"

int main() {

	int		n,m,i,j,ix,iy;
	int 	type_case;

	int	**	grille = Stocker("test.txt", &n, &m);
	int **	grille_user = InitialiserTableau(n,m);
	int ** grille_user_transp = InitialiserTableau(n,m);
	int ** grille_transp = Transposer(grille,n,m);
	int **	I1= IndiceLignes(n,m,grille_transp);
	int **	I2= IndiceLignes(n,m,grille);

	int width = 50*n;
	int height = 50*m;
	int width_interface = 0.2 * width;
	int height_interface = 0.2 * height;
	int width_grille = 0.8 * width;
	int height_grille = 0.8 * height;

	int 	run = 1;
	int erreur = 0;

	SDL_Renderer * renderer;
	SDL_Rect Carre;

	TTF_Font * font;

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


	for (i=width_interface;i<=(width-width_grille/n);i=i+width_grille/n) {
		for (j=height_interface;j<=(height-height_grille/m);j=j+height_grille/m) {

			Carre.x = i;
			Carre.w = width_grille/n * 0.9;
			Carre.y = j;
			Carre.h = height_grille/m * 0.9;
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &Carre);
			SDL_RenderPresent(renderer);
		}

	}

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

							width_grille = width-width_interface;
							height_grille = height-height_interface;
							SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
							SDL_RenderClear(renderer);
							for (i=width_interface;i<=(width-width_grille/n);i=i+width_grille/n) {
								for (j=height_interface;j<=(height-height_grille/m);j=j+height_grille/m) {

									ix = (i-width_interface)/(width_grille/n);
									iy = (j-height_interface)/(height_grille/m);

									Carre.x = i;
									Carre.w = width_grille/n * 0.9;
									Carre.y = j;
									Carre.h = height_grille/m * 0.9;

									SDL_SetRenderDrawColor(renderer, (grille_user[iy][ix] == -1)? 255:0, (grille_user[iy][ix] == 0)? 0:255, (grille_user[iy][ix] == 1)? 0:255, 255);
									SDL_RenderFillRect(renderer, &Carre);
									SDL_RenderPresent(renderer);
								}

							}


							SDL_RenderPresent(renderer);
							printf("Size : %d%d\n", width, height);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (((event.button.x-width_interface)%(width_grille/n)<=0.9*width_grille/n)&&((event.button.y-height_interface)%(height_grille/n)<=0.9*height_grille/m)&&(event.button.x<=width - (0.1 * width_grille/n))&&(event.button.y <= height - (0.1 * height_grille/m))&&(event.button.x>=width_interface)&&(event.button.y>=height_interface)) {
						ix = (int)(event.button.x-width_interface)/(width_grille/n);
						iy = (int)(event.button.y - height_interface)/(height_grille/m);
						Carre.x = ix*(width_grille/n)+width_interface;
						printf("%d %d \n",Carre.x, ix);
						Carre.w = width_grille/n * 0.9;
						Carre.y = iy*(height_grille/m)+height_interface;
						Carre.h = height_grille/m * 0.9;

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

				erreur = VerificationSucces(n,m,I1,I2,grille_user,grille_user_transp);

        printf("\n");

        if (erreur==0) {

          printf("\n\n succès !!!!\n");

          run = 0;

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
	TTF_Quit();
	SDL_Quit();

	return 0;
}
