#ifndef affichage_h
#define affichage_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

char * IndicesLigne(int * ligne, int m);

void AffichageJeu(SDL_Renderer * renderer, SDL_Rect Carre, SDL_Rect * Bouton,SDL_Rect * SaveBouton,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int ** IndiceLignes,int ** IndiceColonnes,int width, int height, int width_grille, int width_interface, int height_grille,int height_interface,int ** grille_user, int m, int n, int essai, char * textEssai, char * buffer, SDL_Surface * texte, SDL_Texture * texture);

void AffichageMenu(SDL_Renderer * renderer,SDL_Rect Carre,SDL_Rect * LoadBouton,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2, int width, int height, SDL_Surface * texte, SDL_Texture * texture);

void Affichagetexte(SDL_Surface * texte, SDL_Texture * texture,char * chaine,SDL_Renderer * renderer,SDL_Rect carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int w, int h);

void AffichageIndice1Ligne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * ligne, int m, int n, int NumLigne, SDL_Surface * texte, SDL_Texture * texture);

void AffichageIndice1Colonne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * colonne, int m, int n, int NumColonne, SDL_Surface * texte, SDL_Texture * texture);

void AffichageIndiceLignes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceLignes, int m, int n, SDL_Surface * texte, SDL_Texture * texture);

void AffichageIndiceColonnes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceColonnes, int m, int n, SDL_Surface * texte, SDL_Texture * texture);

void AffichageGrille(SDL_Renderer * renderer, SDL_Rect Carre,int width, int height, int width_grille, int width_interface, int height_grille, int height_interface,int ** grille_user, int m, int n);

void AffichageBouton(SDL_Renderer * renderer, SDL_Rect * Bouton, int width_interface, int height_interface, SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture);

void AffichageSave(SDL_Renderer * renderer, SDL_Rect * SaveBouton, int width_interface, int height_interface,SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture);

void AffichageLoad(SDL_Renderer * renderer, SDL_Rect * LoadBouton, int width, int height, SDL_Color couleur1,TTF_Font * font, SDL_Surface * texte, SDL_Texture * texture);


void Coloriage(SDL_Event event, SDL_Renderer * renderer, SDL_Rect Carre, int width_interface,int width_grille, int height_interface, int height_grille,int m,int n, int ** grille_user, int ** grille_user_transp);

#endif
