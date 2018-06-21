#include "jeu.h"

int ** InitialisationTableau(int n, int m) {
	int 	i,j;
	int	**	T = (int **)malloc(n * sizeof(int*));

	for (i=0;i<n;i++) {
		T[i] = (int *)malloc(m * sizeof(int));

		for (j=0;j<m;j++) {
			T[i][j] = 0;
		}
	}
	return(T);
}

int ** Transposee(int ** T, int n, int m) {
	int 	i,j;
	int **	Tt = InitialisationTableau(m,n);

	for (i=0;i<m;i++) {
		for (j=0;j<n;j++) {
			Tt[i][j] = T[j][i];
		}
	}

	return Tt;
}

void LiberationTableau(int ** T, int n) {
	int i;
	if (T) {
		for (i=0;i<n;i++) {
			if (T[i])
			{
				free(T[i]);
			}
		}
		free(T);
	}
}

int ** Stockage(char * nom,int * n,int * m) {
	int 	i,j;
	int **	grille;
	FILE * fichier = fopen(nom,"r");

	if (fichier) {
		fscanf(fichier,"%d",n);
		fscanf(fichier,"%d",m);
		grille = InitialisationTableau(*n,*m);

		for (i=0;i<*n;i++) {
			for (j=0;j<*m;j++) {
				fscanf(fichier, "%d", &grille[i][j]);
			}
		}
		fclose(fichier);
	}

	return(grille);

}

int ** IndiceLignes(int n,int m,int ** grille) {
	int		i = 0,
			j = 0,
			indice = 0,
			compteur = 0;
    int	**	indicelign = InitialisationTableau(n,m);

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
    LiberationTableau(grille,n);
    return indicelign;
}

int ComparaisonIndices(int m, int * indiceligne, int * ligne_user) {
	int i = 0,			/*indice parcours ligne_user*/
		j = 0, 			/*indice parcours indiceligne*/
		compteur = 0,	/*compte le nombre de cases remplies du joueur à la suite pour la comparaison avec les indices*/
		erreur = 0;		/*booleen*/

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
		j++;
	}
	return (erreur);
}


int VerificationSucces(int n, int m, int ** IndicesColonnes, int ** IndicesLignes, int ** grille_user, int ** grille_user_transp) {
	int erreur = 0;
	int i=0;
	int j=0;

	while ((i<n)&&erreur==0)
	{
		erreur = ComparaisonIndices(m,IndicesLignes[i],grille_user[i]);
		j=0;
		
		while((j<m)&&erreur==0)
		{
			erreur = ComparaisonIndices(n,IndicesColonnes[j],grille_user_transp[j]);
			j++;
		}
		i++;
	}
	return(erreur);

}

void Sauvegarde(int ** grille_user,int ** IndicesColonnes,int ** IndicesLignes,Tcoup_t * TabCoup,int CompteurCoups, int width,int height,int n, int m, int essai)
{
	int i,j;
	coup_t temp;
	FILE * fichier = fopen("Sauvegarde.txt", "w");

	if (fichier) {

		fprintf(fichier,"%d %d %d %d %d\n",n, m, width,height,essai);
		
		/*Sauvegarde des coups*/
		
		fprintf(fichier,"%d ",CompteurCoups);
		if (CompteurCoups > 0) {
			i = TabCoup->sommet - CompteurCoups + 1;		/*On commence le parcours à l'élément au coup le plus ancien stocké*/
			if (i < 0)									/*La structure étant circulaire, on revient en arrière depuis la fin*/
			{
				i = i + NB_COUPS_TOTAL;
			}
			while (i!=TabCoup->sommet)					/*Parcours de la structure*/
			{
				temp = (TabCoup->base)[i];
				fprintf(fichier,"%d %d %d ",temp.i,temp.j,temp.etatcase); /*Stockage des données*/
				i++;
				if (i == NB_COUPS_TOTAL)				/*Si on dépasse la taille de la structure, on revient au début*/
				{
					i = 0;
				}
			}
		}
		fprintf(fichier,"\n");
				
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

void Chargement(int ** grille_user,int ** IndicesColonnes,int ** IndicesLignes,Tcoup_t * TabCoup,int *PCompteurCoups, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m, int * essai)
{
	int i,j;
	coup_t temp;
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

		grille_user = InitialisationTableau(*n,*m);
		IndicesLignes = InitialisationTableau(*n,*m);
		IndicesColonnes = InitialisationTableau(*m,*n);
		TabCoup = InitialisationCoup(PCompteurCoups);
		
		fscanf(fichier,"%d",PCompteurCoups);
		
		for (i=0;i<*PCompteurCoups;i++)
		{
			fscanf(fichier,"%d",&temp.i);
			fscanf(fichier,"%d",&temp.j);
			fscanf(fichier,"%d",&temp.etatcase);
			(TabCoup->base)[i] = temp;
		}
		TabCoup->sommet = *PCompteurCoups;
		
		
		for (i=0;i<*n;i++)
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",&grille_user[i][j]);
			}
		}
		
		for (i=0;i<*m;i++)
		{
			for (j=0;j<*n;j++)
			{
				fscanf(fichier,"%d",&IndicesColonnes[i][j]);
			}
		}

		for (i=0;i<*n;i++)
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",&IndicesLignes[i][j]);
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

