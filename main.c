#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"

int main()
{

  int run = 1;
  int ix,iy;
  int red, blue, green;
  int n,m,i,j;
  int type_case;
  int ** grille = Stockage("test.txt", &n, &m);
  int ** user_grille = InitialiserTableau(n,m);
  
  
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
                            5+50*n,5+50*m,
                            0);

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
  SDL_RenderClear( renderer );
  
  
  for (i=5;i<50*n;i=i+50) {
	  for (j=5;j<50*m;j=j+50) {
		  
		  Carre.x = i;
		  Carre.w = 45;
		  Carre.y = j;
		  Carre.h = 45;
		  SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
		  SDL_RenderFillRect( renderer, &Carre );
		  SDL_RenderPresent(renderer);
	  }
	  
  }
  



  while (run) {
	  while (SDL_PollEvent(&event)) {
		  
		  switch(event.type)
		{
			case SDL_WINDOWEVENT:
				printf("window event\n");
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						printf("appui sur la croix\n");
						run = 0;
						break;
					/*case SDL_WINDOWEVENT_SIZE_CHANGED:
						width = event.window.data1;
						height = event.window.data2;
						printf("Size : %d%d\n", width, height);*/
				}
			    break;
			case SDL_MOUSEBUTTONDOWN :
				if ((event.button.x<=50*n) && (event.button.y <= 50*m) &&(event.button.x%50>5)&&(event.button.y%50>5)) {
					ix = (int)event.button.x/50;
					iy = (int)event.button.y/50;
					Carre.x = ix*50+5;
					Carre.w = 45;
					Carre.y = iy*50+5;
					Carre.h = 45;
					
	
					if (event.button.button == SDL_BUTTON_LEFT) { 
						if (user_grille[ix][iy]==1) {
							user_grille[ix][iy] = 0;
							blue = 255;
							green = 0;
						}
						else {
							user_grille[ix][iy] = 1;	
							green = 255;
							blue = 0;
						}
						SDL_SetRenderDrawColor( renderer, 0, green, blue, 255 );
											
					}
					else {
						if (user_grille[ix][iy] ==-1) {
							red = 0;
							green =0;
							user_grille[ix][iy] = 0;
						}
						else {
							red =255;
							green = 255;
							user_grille[ix][iy] = -1;
						}
						SDL_SetRenderDrawColor( renderer, red, green, 255, 255 );
					}
				
					SDL_RenderFillRect( renderer, &Carre );
					SDL_RenderPresent(renderer);
					
					
				}
				  /* ici on doit faire des choses */
				  
				break;
			case SDL_QUIT :
				printf("on quitte\n");
				run = 0;
		}
		  
		  
		  
		  
	  }
  /* ici on doit faire des choses */



















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
