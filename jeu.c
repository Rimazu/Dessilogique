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

void LibererTableau(int ** tab, int n) {
	int i;
	if (tab) {
		for (i=0;i<n;i++) {
			if (tab[i]) 
				free(tab[i]);
		}
		free(tab);
	}
}

int ComparerIndices(int m, int * indiceligne, int * ligne_user) {
	int i = 0,			/*indice parcours ligne_user*/
		j = 0, 			/*indice parcours indiceligne*/
		compteur = 0,
		erreur = 0;

	while ((!erreur)&&(i<m)) {
		while ((i<m)&&(ligne_user[i] != 1)) {
			i++;
		}
		compteur=0;
		while ((i<m)&&ligne_user[i] == 1) {
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

	for (i=0;i<m;i++) {
		for (j=0;j<n;j++) {
			Tt[i][j] = T[j][i];
		}
	}

	return Tt;
}


int VerificationSucces(int n, int m, int ** IndicesColonnes, int ** IndicesLignes, int ** grille_user, int ** grille_user_transp) {
	int erreur = 0;
	int i=0;
	int j=0;

	while ((i<n)&&erreur==0)
	{
		erreur = ComparerIndices(m,IndicesLignes[i],grille_user[i]);
		printf("i = %d, erreur = %d \n",i,erreur);
		j=0;
			while((j<m)&&erreur==0)
			{
				erreur = ComparerIndices(n,IndicesColonnes[j],grille_user_transp[j]);
				printf("j = %d, erreur = %d \n",j,erreur);
				j++;
			}
		i++;
	}
	return(erreur);

}

void InitialisationVariables(char * NomGrille,int *** grille, int ***	grille_transp,int ***	grille_user,int ***	grille_user_transp,int	***	IndicesColonnes,int ***	IndicesLignes, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m)
{
	*grille = Stocker(NomGrille, n, m);
	*grille_transp = Transposer(*grille,*n,*m);
	*grille_user = InitialiserTableau(*n,*m);
	*grille_user_transp = InitialiserTableau(*m,*n);
	*IndicesColonnes = IndiceLignes(*m,*n,*grille_transp);
	*IndicesLignes = IndiceLignes(*n,*m,*grille);

	*width = 80*(*m);
	*height = 80*(*n);
	*width_interface = 0.35 * (*width);
	*height_interface = 0.35 * (*height);
	*width_grille = 0.65 * (*width);
	*height_grille = 0.65 * (*height);
}


void Save(int **	grille_user,int	**	IndicesColonnes,int **	IndicesLignes, int width, int height,int n, int m, int essai)
{
	int i,j;
	FILE * fichier = fopen("Sauvegarde.txt", "w");

	if (fichier) {

		fprintf(fichier,"%d %d %d %d %d\n",n, m, width,height,essai);

		fprintf(fichier,"\n"); /* écriture grille_user*/

		for (i=0;i<n;i++)
		{
			for (j=0;j<m;j++)
			{
				fprintf(fichier,"%d ",grille_user[i][j]);
			}
		}
		fprintf(fichier,"\n");

		for (i=0;i<m;i++) /* écriture IndiceColonnes */
		{
			for (j=0;j<n;j++)
			{
				fprintf(fichier,"%d ",IndicesColonnes[i][j]);
			}
		}
		fprintf(fichier,"\n"); /* écriture IndiceLignes */

		for (i=0;i<n;i++)
		{
			for (j=0;j<m;j++)
			{
				fprintf(fichier,"%d ",IndicesLignes[i][j]);
			}
		}
		fprintf(fichier,"\n");

		fclose(fichier);
	}
}

void Load(int ***	grille_user,int ***	grille_user_transp,int	***	IndicesColonnes,int ***	IndicesLignes, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m, int * essai)
{
	int i,j;
	FILE * fichier = fopen("Sauvegarde.txt","r");

	if (fichier)
	{
		fscanf(fichier,"%d",n);
		fscanf(fichier,"%d",m);
		fscanf(fichier,"%d",width);
		fscanf(fichier,"%d",height);
		fscanf(fichier,"%d",essai);

		*width_interface = 0.35 * (*width);
		*height_interface = 0.35 * (*height);
		*width_grille = 0.65 * (*width);
		*height_grille = 0.65 * (*height);

		*grille_user = InitialiserTableau(*n,*m);
		*grille_user_transp = InitialiserTableau(*m,*n);
		*IndicesLignes = InitialiserTableau(*n,*m);
		*IndicesColonnes = InitialiserTableau(*m,*n);


		for (i=0;i<*n;i++)
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",(&(*grille_user)[i][j]));
			}
		}

		*grille_user_transp = Transposer(*grille_user,*n,*m);
		for (i=0;i<*m;i++)
		{
			for (j=0;j<*n;j++)
			{
				fscanf(fichier,"%d",(&(*IndicesColonnes)[i][j]));
			}
		}

		for (i=0;i<*n;i++)
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",(&(*IndicesLignes)[i][j]));
			}
		}


		fclose(fichier);
		remove("Sauvegarde.txt");
	}
	else
	{
		*essai = -666;
	}
}

