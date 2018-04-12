#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


int ** Stocker(char * nom,int * n,int * m) {
	int 	i,j;
	int **	grille;
	FILE * fichier = fopen(nom,"r");

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

/*
int ** IndiceColonnes(int n,int m,int ** grille) {

    return indicecol;
}*/


int ** InitialiserTableau(int n, int m) {
	int 	i,j;
	int	**	tab = (int **)malloc(n * sizeof(int*));

	for (i=0;i<n;i++) {
		tab[i] = (int *)malloc(m * sizeof(int));

		for (j=0;j<m;j++) {
			tab[i][j] = 0;
		}
	}
	return(tab);
}

int ComparerIndices(int n, int * indiceligne, int * ligne_user) {
	int i = 0,			/*indice parcours ligne_user*/
		j = 0, 			/*indice parcours indiceligne*/
		compteur = 0,
		erreur = 0;

	while ((!erreur)&&(i<n)) {
		while ((i<n)&&(!ligne_user[i])) {
			i++;
		}
		compteur=0;
		while ((i<n)&&ligne_user[i]) {
			i++;
			compteur++;
		}
		if (compteur != indiceligne[j]) {
			erreur = 1;
		}
		/*printf("erreurs = %d\n",(compteur != indiceligne[j]));*/
		j++;
	}
	return (erreur);
}

void Afficher(int **T, int n,int m) {
	int	i,j;

	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			printf("%d ",T[i][j]);
		}
		printf("\n");
	}
}

int ** Transposer(int ** T, int n, int m) {
	int 	i,j;
	int **	Tt = InitialiserTableau(m,n);

	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			Tt[i][j] = T[j][i];
		}
	}

	return Tt;
}
