#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


int** stockage(int** grille, char * nom,int* m,int* n) {

	FILE * fichier;

	fichier = fopen(nom,"r");
	if (fichier) {
		fscanf(fichier,&n);
		fscanf(fichier,&m);

		for (i=0;i<*m;i++) {
			for (j=0;j<*n;j++) {
				fscanf(fichier, "%s", grille[i][j]);
			}
		}
		fclose(fichier);
	}

	return(grille);

}

