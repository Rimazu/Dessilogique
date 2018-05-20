#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>
#include "jeu.h"

char * IndicesLigne(int * ligne, int m);

void Affichagetexte(char * chaine,SDL_Renderer * renderer,SDL_Rect carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int w, int h);

void AffichageIndice1Ligne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * ligne, int m, int n, int NumLigne);

void AffichageIndice1Colonne(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int * colonne, int m, int n, int NumColonne);

void AffichageIndiceLignes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceLignes, int m, int n);

void AffichageIndiceColonnes(SDL_Renderer * renderer, SDL_Rect Carre,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int width,int height, int ** IndiceColonnes, int m, int n);
