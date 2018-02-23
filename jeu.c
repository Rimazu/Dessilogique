#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


int** stockage(int** grille, char * nom,int* m,int* n) {
	
	FILE * fichier;
	
	fichier = fopen(nom,"r");
	if (fichier) {
		&m = fgets(fichier);
		&n = fgets(fichier);
		
		for (i=0;i<*m;i++) {
			for (j=0;j<*n;j++) {
				fscanf(fichier, "%s", grille[i][j]);
			}
		}
		fclose(fichier);
	}
	
	return(grille);
	
}


int * IndiceLignes(int n,int m,int ** grille) {
    int i=0,j=0,indice=0,compteur=0;
    int indicelign[n];

    for (i=0;i<n;i++) {
        j=0;
        while (j<m) {
            indice=0;

            while (j<m)&&(0==grille[i][j]) {
                j++;
            }

            while (j<m)&&(1==grille[i][j]) {
                j++;
                indice++;
            }
            if (0!=indice) {
                indicelign[compteur]=indice;
            }
        }
    }
    return indicelign;
}

int * IndiceColonnes(int n,int m,int ** grille) {
    int i=0;,j=0,indice=0,compteur=0;
    int indicecol[m];

    for (j=0;j<m;j++) {
        i=0;
        while (i<n) {
            indice=0;

            while (i<n)&&(0==grille[i][j]) {
                i++;
            }

            while (i<n)&&(1==grille[i][j]) {
                i++;
                indice++;
            }
            if (0!=indice) {
                indicecol[compteur]=indice;
                compteur++;
            }
        }
    }
    return indicecol;
}
