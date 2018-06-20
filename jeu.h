#ifndef JEU
#define JEU

#include "commun.h"

/*Renvoie le tableau qui contient les indices des lignes de la grille*/
int ** IndiceLignes(int n,int m,int ** grille);

/*Renvoie le tableau qui contient les indices des colonnes de la grille
int ** IndiceColonnes(int n,int m,int ** grille);*/


/*Stocke la matrice du fichier dans un tableau*/
int ** Stocker(char *,int*,int*);

/*Initialise un tableau*/
int ** InitialiserTableau(int,int);

/*Libère le tableau*/
void LibererTableau(int **,int);

/*Compare la ligne des indices et celle du joueur (pour ligne : mettre m, pour colonne : mettre n)*/
int ComparerIndices(int n, int * indiceligne, int * ligne_user);

/*Affiche les elements d'un tableau*/
void Afficher(int **T, int n,int m);

/*Renvoie la transposee d'une matrice*/
int ** Transposer(int ** T, int n, int m);

/*Compare le résultat avec la solution */
int VerificationSucces(int n, int m, int ** IndicesColonnes, int ** IndicesLignes, int ** grille_user, int ** grille_user_transp);

void InitialisationVariables(char * NomGrille,int *** grille, int ***	grille_transp,int ***	grille_user,int ***	grille_user_transp,int	***	IndicesColonnes,int ***	IndicesLignes, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m);

void Save(int ** grille,int **	grille_user,int	**	IndicesColonnes,int **	IndicesLignes, int width, int height,int n, int m, int essai);

void Load(int *** grille, int *** grille_transp,int ***	grille_user,int ***	grille_user_transp,int	***	IndicesColonnes,int ***	IndicesLignes, int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m, int * essai);

Tcoup_t * InitialiserCoup();

Tcoup_t * MajCoup(Tcoup_t * TabCoup, int i, int j, int etat) ;

Tcoup_t * AnnulerCoup(Tcoup_t * TabCoup);

void LibererCoups(Tcoup_t * TabCoup);

#endif
