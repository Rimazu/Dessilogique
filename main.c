#include "jeu.h"
#include "affichage.h"

int main() {

	int					n,m,
						essai=0;

	int				**	grille = NULL,
					**	grille_transp = NULL,
					**	grille_user = NULL,
					**	grille_user_transp = NULL,
					**	IndicesColonnes = NULL,
					**	IndicesLignes = NULL;

	Tcoup_t			*	TabCoup = InitialiserCoup();

	int					width = 400,
						height = 400,
						width_interface = 0.35 * width,
						height_interface = 0.35 * height,
						width_grille = 0.65 * width,
						height_grille = 0.65 * height;


	char				textEssai[80],
						buffer[3],
						etat[10]="menu";

	int 				run = 1,
						erreur = 0;

	SDL_Renderer	*	renderer;
	SDL_Surface 	*	texte = NULL;
	SDL_Texture		*	texture = NULL;
	SDL_Rect 			Carre;
	SDL_Rect 			Bouton;
	SDL_Rect			SaveLoadBouton;


	TTF_Font		*	font;
	SDL_Color couleurNoire = {0,0,0,0};
	SDL_Color couleurRouge = {255,0,0,0};

	/* variable d'initialisation de SDL_image */
	int 				flags = IMG_INIT_JPG | IMG_INIT_PNG;
	/* variable liee a la fenetre */
	SDL_Window		*	window;
	/* variables liees a la capture d'evenement */
	SDL_Event			event;

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
	font = TTF_OpenFont("arial.ttf",45);

	printf("Evenements initialisés !\n");

	AffichageMenu(renderer,Carre,&SaveLoadBouton,font,couleurNoire,couleurRouge,width,height,texte,texture);

	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT:
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
							run = 0;
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = event.window.data1;
							height = event.window.data2;


							if (strcmp(etat,"menu")==0)
							{
									AffichageMenu(renderer,Carre,&SaveLoadBouton,font,couleurNoire,couleurRouge,width,height,texte,texture);
							}
							else
							{
								width_interface = 0.35 * width;
								height_interface = 0.35 * height;
								width_grille = 0.65 * width;
								height_grille = 0.65 * height;
								font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
								AffichageJeu(renderer,Carre,&Bouton,&SaveLoadBouton,font,couleurNoire,couleurRouge,IndicesLignes,IndicesColonnes,width,height,width_grille,width_interface,height_grille,height_interface,grille_user,m,n,essai,textEssai,buffer,texte,texture);
								if (strcmp(etat,"succes")==0)
								{
									Affichagetexte(texte,texture,"Success",renderer,Carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
								}

							}
					}
							break;
				case SDL_MOUSEBUTTONDOWN:
					if (strcmp(etat,"succes")==0)
					{
						strcpy(etat,"menu");
						essai = 0;
						AffichageMenu(renderer,Carre,&SaveLoadBouton,font,couleurNoire,couleurRouge,width,height,texte,texture);
					}
					else
					{
						if (strcmp(etat,"jeu")==0)
						{
							if (((event.button.x-width_interface)%(width_grille/m)<=0.9*width_grille/m)&&((event.button.y-height_interface)%(height_grille/n)<=0.9*height_grille/n)&&(event.button.x<=width - (0.1 * width_grille/m))&&(event.button.y <= height - (0.1 * height_grille/n))&&(event.button.x>=width_interface)&&(event.button.y>=height_interface)) {
								Coloriage(event, renderer,Carre,width_interface,width_grille,height_interface,height_grille,m,n,grille_user,grille_user_transp,TabCoup);
							}
							else
							{
								if ((event.button.x >=Bouton.x)&&(event.button.x <= Bouton.x + Bouton.w)&&(event.button.y >=Bouton.y)&&(event.button.y <=Bouton.y + Bouton.h))
								{
									erreur = VerificationSucces(n,m,IndicesColonnes,IndicesLignes,grille_user,grille_user_transp);
									if (erreur==0) {

											strcpy(etat,"succes");

											Affichagetexte(texte,texture,"Success",renderer,Carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);

										}
										else {
											essai++;
											sprintf(buffer,"%d",essai);
											strcpy(textEssai,"Echecs : ");
											strcat(textEssai, buffer);
											Affichagetexte(texte,texture,textEssai,renderer,Carre,font,couleurNoire,couleurRouge,Bouton.x,Bouton.y+Bouton.h,Bouton.w,Bouton.h);
										}
								}
								else
								{
									if ((event.button.x >=SaveLoadBouton.x)&&(event.button.x <= SaveLoadBouton.x + SaveLoadBouton.w)&&(event.button.y >=SaveLoadBouton.y)&&(event.button.y <=SaveLoadBouton.y + SaveLoadBouton.h))
									{
										Save(grille,grille_user,IndicesColonnes,IndicesLignes,width,height,n,m,essai);
										Affichagetexte(texte,texture,"Sauvegarde !",renderer,Carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
										strcpy(etat,"succes");
									}
								}
							}
						}
						else
						{
							if (strcmp(etat,"menu")==0)
							{
								if ((event.button.x >=SaveLoadBouton.x)&&(event.button.x <= SaveLoadBouton.x + SaveLoadBouton.w)&&(event.button.y >=SaveLoadBouton.y)&&(event.button.y <=SaveLoadBouton.y + SaveLoadBouton.h))
								{
									Load(&grille,&grille_transp,&grille_user,&grille_user_transp,&IndicesColonnes,&IndicesLignes,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m,&essai);
									if (essai == -666)
									{
										Affichagetexte(texte,texture,"ERREUR DE CHARGEMENT",renderer,Carre,font,couleurNoire,couleurRouge,0,height/4,width,height/2);
											strcpy(etat,"succes");
									}
									else
									{
										strcpy(etat,"jeu");
									}


								}
								else
								{
									if (event.button.y > height/5)
									{
										strcpy(etat,"jeu");
										if (event.button.x < width/3)
										{
				
												InitialisationVariables("Grille1.txt", &grille, &grille_transp, &grille_user, &grille_user_transp, &IndicesColonnes, &IndicesLignes,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m);
										}
										else
										{
											if ((event.button.x >= width/3) && (event.button.x < 2*width/3))
											{
												
												InitialisationVariables("Grille2.txt", &grille, &grille_transp, &grille_user, &grille_user_transp, &IndicesColonnes, &IndicesLignes,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m);
											}
											else
											{
												
												InitialisationVariables("Grille3.txt", &grille, &grille_transp, &grille_user, &grille_user_transp, &IndicesColonnes, &IndicesLignes,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m);
											}
										}
									}
								}
								if (strcmp(etat,"jeu")==0)
								{
								SDL_SetWindowSize(window, width, height);
								font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
								AffichageJeu(renderer,Carre,&Bouton,&SaveLoadBouton,font,couleurNoire,couleurRouge,IndicesLignes,IndicesColonnes,width,height,width_grille,width_interface,height_grille,height_interface,grille_user,m,n,essai, textEssai, buffer,texte,texture);
								}
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
	
	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texture);
	/* on libere la fenetre */
	SDL_DestroyWindow(window);
	/* fermeture de SDL_image, SDL_ttf et SDL2 */
	IMG_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	LibererCoups(TabCoup);
	LibererTableau(grille,n);
	LibererTableau(grille_transp,n);
	LibererTableau(grille_user,n);
	LibererTableau(grille_user_transp,n);
	LibererTableau(IndicesLignes,n);
	LibererTableau(IndicesColonnes,n);

	return 0;
}
