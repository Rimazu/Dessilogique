#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


int** Stockage(int** grille, char * nom,int* m,int* n) {

	FILE * fichier;
	int i,j;

	fichier = fopen(nom,"r");
	if (fichier) {
		fscanf(fichier,n);
		fscanf(fichier,m);

		for (int i=0;i<*n;i++) {
			for (int j=0;j<*m;j++) {
				fscanf(fichier, "%s", grille[i][j]);
			}
		}
		fclose(fichier);
	}

	return(grille);

}

int ** IndiceLignes(int n,int m,int ** grille) {
    int i=0,j=0,indice=0,compteur=0;
    int indicelign[n][m]=InitialiserTableau(n,m);

    for (i=0;i<n;i++) {
        j=0;
        while (j<m) {
            indice=0;

            while ((j<m)&&(0==grille[i][j])) {
                j++;
            }

            while ((j<m)&&(1==grille[i][j])) {
                j++;
                indice++;
            }
            indicelign[i][compteur]=indice;
            compteur++;
        }
    }
    return indicelign;
}

int ** IndiceColonnes(int n,int m,int ** grille) {
    int i=0,j=0,indice=0,compteur=0;
    int indicecol[m][n]=InitialiserTableau(m,n);

    for (j=0;j<m;j++) {
        i=0;
        while (i<n) {
            indice=0;

            while ((i<n)&&(0==grille[i][j])) {
                i++;
            }

            while ((i<n)&&(1==grille[i][j])) {
                i++;
                indice++;
            }
            indicecol[j][compteur]=indice;
            compteur++;
        }
    }
    return indicecol;
}

int ** InitialiserTableau(int n, int m) {
	int i,j;
	int tab[n][m];
	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			tab[i][j]=0;
		}
	}

	return(tab);
}
