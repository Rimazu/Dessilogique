#include <stdio.h>
#include <stdlib.h>

/*renvoie le tableau qui contient les indices des lignes de la grille*/
int ** IndiceLignes(int n,int m,int ** grille);

/*renvoie le tableau qui contient les indices des colonnes de la grille*/
int ** IndiceColonnes(int n,int m,int ** grille);


/*stocke la matrice du fichier dans un tableau*/
int ** Stockage(char *,int*,int*);

/*Initialise un tableau*/
int ** InitialiserTableau(int,int);
