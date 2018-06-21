#include "commun.h"
#include "jeu.h"
#include "affichage.h"


int main() {

	int					n,m,
						essai = 0,
						CompteurCoups = 0;

	int				**	grille = NULL,
					**	grille_transp = NULL,
					**	grille_user = NULL,
					**	grille_user_transp = NULL,
					**	IndicesColonnes = NULL,
					**	IndicesLignes = NULL;

	Tcoup_t			*	TabCoup = NULL;

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
	SDL_Rect 			carre;
	SDL_Rect 			BoutonVerif;
	SDL_Rect			BoutonSauvCharg;
	SDL_Rect 			BoutonAnnuler;


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

	AffichageMenu(renderer,carre,&BoutonSauvCharg,font,couleurNoire,couleurRouge,width,height,texte,texture);

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
								AffichageMenu(renderer,carre,&BoutonSauvCharg,font,couleurNoire,couleurRouge,width,height,texte,texture);
							}
							else
							{
								width_interface = 0.35 * width;
								height_interface = 0.35 * height;
								width_grille = 0.65 * width;
								height_grille = 0.65 * height;
								font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
								AffichageJeu(renderer,carre,&BoutonVerif,&BoutonSauvCharg,&BoutonAnnuler,font,couleurNoire,couleurRouge,IndicesLignes,IndicesColonnes,width,height,width_grille,width_interface,height_grille,height_interface,grille_user,m,n,essai,textEssai,buffer,texte,texture);
								if (strcmp(etat,"succes")==0)
								{
									AffichageTexte(texte,texture,"Success",renderer,carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
								}

							}
					}
				break;
				case SDL_MOUSEBUTTONDOWN:
					if (strcmp(etat,"succes")==0)
					{
						strcpy(etat,"menu");
						essai = 0;
						AffichageMenu(renderer,carre,&BoutonSauvCharg,font,couleurNoire,couleurRouge,width,height,texte,texture);
					}
					else
					{
						if (strcmp(etat,"jeu")==0)
						{
							if (((event.button.x-width_interface)%(width_grille/m)<=0.9*width_grille/m)&&((event.button.y-height_interface)%(height_grille/n)<=0.9*height_grille/n)&&(event.button.x<=width - (0.1 * width_grille/m))&&(event.button.y <= height - (0.1 * height_grille/n))&&(event.button.x>=width_interface)&&(event.button.y>=height_interface)) {
								Coloriage(event, renderer,carre,width_interface,width_grille,height_interface,height_grille,m,n,grille_user,grille_user_transp,TabCoup,&CompteurCoups);

							}
							else
							{
								if ((event.button.x >=BoutonVerif.x)&&(event.button.x <= BoutonVerif.x + BoutonVerif.w)&&(event.button.y >=BoutonVerif.y)&&(event.button.y <=BoutonVerif.y + BoutonVerif.h))
								{
									erreur = VerificationSucces(n,m,IndicesColonnes,IndicesLignes,grille_user,grille_user_transp);
									if (erreur==0) {

											strcpy(etat,"succes");

											AffichageTexte(texte,texture,"Success",renderer,carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);

										}
										else {
											essai++;
											sprintf(buffer,"%d",essai);
											strcpy(textEssai,"Echecs : ");
											strcat(textEssai, buffer);
											AffichageTexte(texte,texture,textEssai,renderer,carre,font,couleurNoire,couleurRouge,BoutonVerif.x,17*height_interface/30,BoutonVerif.w,height_interface/3);
						
										}	
								}
								else
								{
									if ((event.button.x >=BoutonSauvCharg.x)&&(event.button.x <= BoutonSauvCharg.x + BoutonSauvCharg.w)&&(event.button.y >=BoutonSauvCharg.y)&&(event.button.y <=BoutonSauvCharg.y + BoutonSauvCharg.h))
									{
										Sauvegarde(grille_user,IndicesColonnes,IndicesLignes,TabCoup,CompteurCoups,width,height,n,m,essai);
										AffichageTexte(texte,texture,"Sauvegarde !",renderer,carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
										strcpy(etat,"succes");
									}
									else {
										if ((event.button.x >=BoutonAnnuler.x)&&(event.button.x <= BoutonAnnuler.x + BoutonAnnuler.w)&&(event.button.y >=BoutonAnnuler.y)&&(event.button.y <=BoutonAnnuler.y + BoutonAnnuler.h))
										{
											AnnulationCoup(TabCoup,&CompteurCoups,grille_user,grille_user_transp,renderer,carre,width_interface,width_grille,height_interface, height_grille,m,n);
										}
									}
								}
							}
						}
						else
						{
							if (strcmp(etat,"menu")==0)
							{
								if ((event.button.x >=BoutonSauvCharg.x)&&(event.button.x <= BoutonSauvCharg.x + BoutonSauvCharg.w)&&(event.button.y >=BoutonSauvCharg.y)&&(event.button.y <=BoutonSauvCharg.y + BoutonSauvCharg.h))
								{
									Chargement(grille_user,IndicesColonnes,IndicesLignes,TabCoup, &CompteurCoups,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m,&essai);
									grille_user_transp = InitialisationTableau(m,n);
									grille_user_transp = Transposee(grille_user,n,m);
									if (essai == -666)
									{
										AffichageTexte(texte,texture,"ERREUR DE CHARGEMENT",renderer,carre,font,couleurNoire,couleurRouge,0,height/4,width,height/2);
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
										
										sprintf(buffer,"%d",1+(3*event.button.x/width));
										strcpy(textEssai,"Grille");
										strcat(textEssai, buffer);
										strcpy(buffer,".txt");
										strcat(textEssai, buffer);
										
										grille = Stockage(textEssai, &n, &m);
										grille_transp = Transposee(grille,n,m);
										grille_user = InitialisationTableau(n,m);
										grille_user_transp = InitialisationTableau(m,n);
										IndicesColonnes = IndiceLignes(m,n,grille_transp);
										IndicesLignes = IndiceLignes(n,m,grille);
										TabCoup = InitialisationCoup(&CompteurCoups);

										width = 80*m;
										height = 80*n;
										width_interface = 0.35 *width;
										height_interface = 0.35 *height;
										width_grille = 0.65 *width;
										height_grille = 0.65 *height;
									}
								}
								if (strcmp(etat,"jeu")==0)
								{
								SDL_SetWindowSize(window, width, height);
								font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
								AffichageJeu(renderer,carre,&BoutonVerif,&BoutonSauvCharg,&BoutonAnnuler,font,couleurNoire,couleurRouge,IndicesLignes,IndicesColonnes,width,height,width_grille,width_interface,height_grille,height_interface,grille_user,m,n,essai, textEssai, buffer,texte,texture);
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
	LiberationCoups(TabCoup);
	LiberationTableau(grille_user,n);
	LiberationTableau(grille_user_transp,n);
	LiberationTableau(IndicesLignes,n);
	LiberationTableau(IndicesColonnes,n);

	return 0;
}
