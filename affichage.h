#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>
#include "jeu.h"

char * AfficherIndicesLigne(int * ligne, int m);

void Affichagetexte(char * chaine,SDL_Renderer * renderer,TTF_Font * font,SDL_Color couleur1, SDL_Color couleur2,int x,int y,int width_interface, int height_interface);
