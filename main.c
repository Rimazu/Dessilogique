#include "commun.h"
#include "jeu.h"
#include "affichage.h"





int main() {
	
	
	
	/* Initialisations variables entières*/

	int					n,m,
						essai = 0,
						CompteurCoups = 0;
						
						
						
	int					width = 400,
						height = 400,
						width_interface = 0.35 * width,
						height_interface = 0.35 * height,
						width_grille = 0.65 * width,
						height_grille = 0.65 * height;
						
	int 				run = 1,
						erreur = 0;

	/* Initialisation Tableaux */

	int				**	grille = NULL,
					**	grille_transp = NULL,
					**	grille_user = NULL,
					**	grille_user_transp = NULL,
					**	IndicesColonnes = NULL,
					**	IndicesLignes = NULL;

	/* Initialisation Structure */

	Tcoup_t			*	TabCoup = NULL;


	/* Initialisation Strings */

	char				textEssai[80],
						buffer[10],
						etat[10]="menu";

	/* Initialisation variables SDL */

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


	/* ouverture de la fenetre */
	window = SDL_CreateWindow("Dessilogique",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														width,height,
														SDL_WINDOW_RESIZABLE);

	if(!window){
		fprintf(stderr,"Erreur de creation de la fenetre : %s\n", SDL_GetError());
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* initialisation du renderer */
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(!renderer){
		fprintf(stderr,"Erreur de creation du renderer\n");
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	printf("SDL initialisée !\n");


	/*initialisation de la police*/
	font = TTF_OpenFont("arial.ttf",45);

	printf("Evenements initialisés !\n");

	AffichageMenu(renderer,carre,&BoutonSauvCharg,font,couleurNoire,couleurRouge,width,height,texte,texture);  /* Affichage du menu au lancement du jeu*/

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
						case SDL_WINDOWEVENT_SIZE_CHANGED:		/* Rechargement du menu ou de l'écran de jeu après un changement de taille de fenêtre*/
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
					if (strcmp(etat,"succes")==0)	/* Etat d'attente d'un clic de confirmation avant de retourner au menu*/
					{
						strcpy(etat,"menu");
						essai = 0;   		/* Remise à zero des variables modifiées */
						width = 400;
						height = 400;
						SDL_SetWindowSize(window,width,height);
						SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
						AffichageMenu(renderer,carre,&BoutonSauvCharg,font,couleurNoire,couleurRouge,width,height,texte,texture);
					}
					else
					{
						if (strcmp(etat,"jeu")==0)
						{	
							if (((event.button.x-width_interface)%(width_grille/m)<=0.9*width_grille/m)&&((event.button.y-height_interface)%(height_grille/n)<=0.9*height_grille/n)&&(event.button.x<=width - (0.1 * width_grille/m))&&(event.button.y <= height - (0.1 * height_grille/n))&&(event.button.x>=width_interface)&&(event.button.y>=height_interface)) {
								Coloriage(event, renderer,carre,width_interface,width_grille,height_interface,height_grille,m,n,grille_user,grille_user_transp,TabCoup,&CompteurCoups);
								/* Colorie la case qui vient d'être cliquée selon sa couleur actuelle*/
							}
							else
							{
								if ((event.button.x >=BoutonVerif.x)&&(event.button.x <= BoutonVerif.x + BoutonVerif.w)&&(event.button.y >=BoutonVerif.y)&&(event.button.y <=BoutonVerif.y + BoutonVerif.h))
								{		
									/* Appuie sur le bouton "Vérification" donc recherche d'erreur dans la correspondance de la grille du joueur avec les indices */
									
									erreur = VerificationSucces(n,m,IndicesColonnes,IndicesLignes,grille_user,grille_user_transp);
									if (erreur==0) {

											strcpy(etat,"succes");  /*Passage à l'état de "succès" */

											AffichageTexte(texte,texture,"Bravo !",renderer,carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
											SDL_RenderPresent(renderer);

										}
										else {
											essai++;				/* Incrémentation du nombre d'echec*/
											sprintf(buffer,"%d",essai);
											strcpy(textEssai,"Echecs : ");
											strcat(textEssai, buffer);
											AffichageTexte(texte,texture,textEssai,renderer,carre,font,couleurNoire,couleurRouge,BoutonVerif.x,17*height_interface/30,BoutonVerif.w,height_interface/3);
											SDL_RenderPresent(renderer);
										}	
								}
								else
								{
									if ((event.button.x >=BoutonSauvCharg.x)&&(event.button.x <= BoutonSauvCharg.x + BoutonSauvCharg.w)&&(event.button.y >=BoutonSauvCharg.y)&&(event.button.y <=BoutonSauvCharg.y + BoutonSauvCharg.h))
									{	
										/* Appuie sur le bouton de Sauvegarde*/
											
										Sauvegarde(grille_user,IndicesColonnes,IndicesLignes,TabCoup,CompteurCoups,width,height,n,m,essai);
										AffichageTexte(texte,texture,"Sauvegarde !",renderer,carre,font,couleurNoire,couleurRouge,0,0,width_interface,height_interface);
										strcpy(etat,"succes");		/* Passage à l'état de "succès"*/
										SDL_RenderPresent(renderer);
									}
									else {
										if ((event.button.x >=BoutonAnnuler.x)&&(event.button.x <= BoutonAnnuler.x + BoutonAnnuler.w)&&(event.button.y >=BoutonAnnuler.y)&&(event.button.y <=BoutonAnnuler.y + BoutonAnnuler.h))
										{	/* Appuie sur le bouton d'annulation */
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
									/* Appuie sur le bouton de chargement d'une partie*/
									
									LiberationTableau(grille_user_transp,m); /* Libération du tableau pour le ré-allouer plus loin avec de nouvelles dimensions*/
									Chargement(&grille_user,&IndicesColonnes,&IndicesLignes,&TabCoup, &CompteurCoups,&width,&height,&width_interface,&width_grille,&height_interface,&height_grille,&n,&m,&essai);
									grille_user_transp = Transposee(grille_user,n,m); 
									
									if (essai == -666) 					/* Tentative de chargement infructueuse, -666 étant la valeur renvoyée par chargement en cas d'echec d'ouverture de fichier*/
									{
										AffichageTexte(texte,texture,"ERREUR DE CHARGEMENT",renderer,carre,font,couleurNoire,couleurRouge,0,height/4,width,height/2);
										
										strcpy(etat,"succes"); 			/* Passage à l'état de "succès" malgré le...non-succès*/
										SDL_RenderPresent(renderer);
									}
									else
									{
										strcpy(etat,"jeu"); 			/* Passage à l'état de "jeu" */
									}
								}
								else 	/* On est dans le menu */
								{
									if (event.button.y > height/5) 		/* On appuie sur une des cases "grille" */
									{
										strcpy(etat,"jeu"); 			/* On passe à l'état "jeu" */
										
										
										sprintf(buffer,"%d",1+(3*event.button.x/width));  
										strcpy(textEssai,"Grille");
										strcat(textEssai, buffer);
										strcpy(buffer,".txt");
										strcat(textEssai, buffer);		/* textEssai contient "GrilleX.txt" avec X le numéro de grille choisi*/
										
										/* Initialisation des tableaux et variables selon la grille choisie */
										
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
									/* Si On a appuyé sur le bouton Charger ou une grille, alors affichage de la fenêtre de jeu */
									
									SDL_SetWindowSize(window, width, height);
									font = TTF_OpenFont("arial.ttf",45*width*height/(80*n*80*m));
									AffichageJeu(renderer,carre,&BoutonVerif,&BoutonSauvCharg,&BoutonAnnuler,font,couleurNoire,couleurRouge,IndicesLignes,IndicesColonnes,width,height,width_grille,width_interface,height_grille,height_interface,grille_user,m,n,essai, textEssai, buffer,texte,texture);
									SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);  
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
	/* fermeture de SDL_ttf et SDL2 */
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
