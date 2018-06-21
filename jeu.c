#include "jeu.h"

int ** InitialisationTableau(int n, int m) {		/* n : nombre de lignes, m : nombre de colonnes */
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
	if (T) {					/*On libere les pointeurs s'ils ne sont pas NULL*/
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
		grille = InitialisationTableau(*n,*m);	/* Initialisation de la grille à remplir */

		for (i=0;i<*n;i++) {
			for (j=0;j<*m;j++) {
				fscanf(fichier, "%d", &grille[i][j]);	/* remplissage de la grille avec les valeurs lues dans le fichier */
			}
		}
		fclose(fichier);
	}

	return(grille);

}

int ** IndiceLignes(int n,int m,int ** grille) {
	int		i = 0,
			j = 0,
			indice = 0,							/* compteur pour le nombre de "1" successifs */
			compteur = 0;						/* compteur pour la position de indice dans le tableau indicelign */
    int	**	indicelign = InitialisationTableau(n,m);

    for (i=0;i<n;i++) {							/* Pour chaque ligne de la grille */
        j=0;
        compteur=0;
        while (j<m) {							/* Parcours d'une ligne */
            indice=0;

            while ((j<m)&&(0==grille[i][j])) {	/* On passe les "0" successifs*/
                j++;
            }

            while ((j<m)&&(1==grille[i][j])) {	/* On compte les "1" successifs en incrémentant le compteur */
                j++;
                indice++;
            }
            indicelign[i][compteur]=indice;		/* Mettre le nombre de 1 successif dans le tableau d'indices */
            compteur++;							/* Passer à la position suivante pour stocker le prochain indice */
        }
    }
    LiberationTableau(grille,n);				/* Libérer la grille initiale qui ne sera plus utilisée dans la suite du programme */
    return indicelign;
}

int ComparaisonIndices(int m, int * indiceligne, int * ligne_user) {		/* Compare 1 ligne de la grille et ses indices respectifs et retourne un booléen d'erreur */
	int i = 0,			/*indice parcours ligne_user*/
		j = 0, 			/*indice parcours indiceligne*/
		compteur = 0,	/*compte le nombre de cases remplies du joueur à la suite pour la comparaison avec les indices*/
		erreur = 0;		/*booleen*/

	while ((!erreur)&&(i<m)) { /* Tant qu'on n'a pas trouvé d'erreur, ni n'a fini le parcours de la grille utilisateur */
		while ((i<m)&&(ligne_user[i] != 1)) {
			i++;
		}
		compteur=0;
		while ((i<m)&&ligne_user[i] == 1) {	/* Compte le nombre de 1 qui se suivent et compare avec l'indice, si ils sont différent, il y a une erreur */
			i++;
			compteur++;
		}
		if (compteur != indiceligne[j]) {
			erreur = 1;
		}
		j++;	/* On passe à la prochaine succession de 1 */
	}
	return (erreur);
}


int VerificationSucces(int n, int m, int ** IndicesColonnes, int ** IndicesLignes, int ** grille_user, int ** grille_user_transp) {	/* Execute ComparaisonIndices sur chaque lignes et colonnes et retourne un booléen d'erreur */
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

void Sauvegarde(int ** grille_user,int ** IndicesColonnes,int ** IndicesLignes,Tcoup_t * TabCoup,int CompteurCoups, int width,int height,int n, int m, int essai) /* Sauvegarde n, m, weight, height, essai, Tabcoup, urille_user, IndicesLignes et IndicesColonnes dans "Sauvegarde.txt" */
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
			do 				/*Parcours de la structure*/
			{
				temp = (TabCoup->base)[i];
				fprintf(fichier,"%d %d %d ",temp.i,temp.j,temp.etatcase); /*Stockage des données*/
				i++;
				if (i == NB_COUPS_TOTAL)				/*Si on dépasse la taille de la structure, on revient au début*/
				{
					i = 0;
				}
			} while (i!=1+TabCoup->sommet);
		}
		fprintf(fichier,"\n");
				
		for (i=0;i<n;i++)	/* écriture de la grille joueur */
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
		fprintf(fichier,"\n"); 

		for (i=0;i<n;i++) /* écriture IndiceLignes */
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


void Chargement(int *** Pgrille_user,int *** PIndicesColonnes,int *** PIndicesLignes,Tcoup_t ** PTabCoup,int *PCompteurCoups, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m, int * essai)
{		/* Extraie toutes les informations de "Sauvegarde.txt" */
	int i,j;
	coup_t temp;
	FILE * fichier = fopen("Sauvegarde.txt","r");

	if (fichier)
	{
		
		/* Libération et réallocation des tableaux avec leurs nouvelles dimensions */
		
		LiberationTableau(*Pgrille_user,*n);
		LiberationTableau(*PIndicesLignes,*n);
		LiberationTableau(*PIndicesColonnes,*m);
		LiberationCoups(*PTabCoup);
		
		/* Mise à jour des variables */
		
		fscanf(fichier,"%d",n);
		fscanf(fichier,"%d",m);
		fscanf(fichier,"%d",width);
		fscanf(fichier,"%d",height);
		fscanf(fichier,"%d",essai);

		*width_interface = 0.35 * (*width);
		*height_interface = 0.35 * (*height);
		*width_grille = 0.65 * (*width);
		*height_grille = 0.65 * (*height);
		
		/* Nouvelle initialisation des tableaux et autres structures */
		
		*Pgrille_user = InitialisationTableau(*n,*m);

		*PIndicesLignes = InitialisationTableau(*n,*m);
		*PIndicesColonnes = InitialisationTableau(*m,*n);
		*PTabCoup = InitialisationCoup(PCompteurCoups);
		
		fscanf(fichier,"%d",PCompteurCoups); 
		
		for (i=0;i<*PCompteurCoups;i++) /* Chargement de la structure de gestion des coups */
		{
			fscanf(fichier,"%d",&temp.i);
			fscanf(fichier,"%d",&temp.j);
			fscanf(fichier,"%d",&temp.etatcase);
			((*PTabCoup)->base)[i] = temp;
		}
		
		(*PTabCoup)->sommet = *PCompteurCoups - 1;
		
		for (i=0;i<*n;i++) 				/* Chargement de la grille utilisateur */
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",&(*Pgrille_user)[i][j]);
			}
		}
		
		for (i=0;i<*m;i++)				/* Chargement du tableau des indices des colonnes */
		{
			for (j=0;j<*n;j++)
			{
				fscanf(fichier,"%d",&(*PIndicesColonnes)[i][j]);
			}
		}
		

		for (i=0;i<*n;i++)				/* Chargement du tableau des indices des lignes */
		{
			for (j=0;j<*m;j++)
			{
				fscanf(fichier,"%d",&(*PIndicesLignes)[i][j]);
			}
		}

		fclose(fichier);
	}
	else
	{
		*essai = -666;
	}
}

