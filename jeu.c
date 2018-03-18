#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


int** Stockage(char * nom,int* n,int* m) {

	FILE * fichier;
	int i,j;
	int ** grille;
	fichier = fopen(nom,"r");
	if (fichier) {
		fscanf(fichier,"%d",n);
		fscanf(fichier,"%d",m);

		grille = InitialiserTableau(*n,*m);


		for (i=0;i<*n;i++) {
			for (j=0;j<*m;j++) {
				fscanf(fichier, "%d", &grille[i][j]);
				/*printf("%d \t %d %d \n",grille[i][j],i,j);*/
			}
		}
		fclose(fichier);
	}

	return(grille);

}

int ** IndiceLignes(int n,int m,int ** grille) {
    int i=0,j=0,indice=0,compteur=0;
    int **indicelign=InitialiserTableau(n,m);

    for (i=0;i<n;i++) {
        j=0;
        compteur=0;
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
    int i=0,j=0,indice=0,compteur;
    int **indicecol=InitialiserTableau(m,n);

    for (j=0;j<m;j++) {
        i=0;
        compteur=0;
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
	int ** tab;


	tab = (int **)malloc(n * sizeof(int*));

	for (i=0;i<n;i++) {
		tab[i] = (int *)malloc(m * sizeof(int));
		for (j=0;j<m;j++) {
			tab[i][j]=0;
		}
	}

	return(tab);
}

void AfficherM(int **C, int n,int m) {
	int 		i,j;

	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			printf("%d ",C[i][j]);
		}
		printf("\n");
		}
	}




	int comparer_indices(int m, int * indices, int * a_comparer)
	{
		int i = 0;
		int j = 0;
		int erreur = 0;
		int compteur = 0;


		while ((indices[i] != 0)&&(i<m))
		{
			while ((erreur == 0)&&(compteur != indices[i])&&(j<m))
			{
				if (a_comparer)[j]) {
					compteur++
					j++;
				}
				else {
					if (compteur != 0) {
						erreur = 1;
					}
					else {
						compteur = 0;
						j++;
					}
				}
			}
			i++;
		}
		return(erreur==0);
	}
