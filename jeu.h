#ifndef JEU_H
#define JEU_H

#include "commun.h"

/*Fonctions générales de gestion de matrice*/
int ** InitialisationTableau(int,int);				/*Initialise un tableau*/

int ** Transposee(int ** T, int n, int m);		/*Renvoie la transposee d'une matrice*/

void LiberationTableau(int ** T,int n);			/*Libère le tableau*/

/*Fonctions pour le moteur du jeu*/
int ** Stockage(char * nom,int * n,int * m);		/*Stocke la matrice du fichier dans un tableau*/

int ** IndiceLignes(int n,int m,int ** grille); /*Renvoie le tableau qui contient les indices des lignes de la grille*/

int ComparaisonIndices(int n, int * indiceligne, int * ligne_user); /*Compare la ligne des indices et celle du joueur (pour ligne : mettre m, pour colonne : mettre n)*/

int VerificationSucces(int n, int m, int ** IndicesColonnes, int ** IndicesLignes, int ** grille_user, int ** grille_user_transp); /*Compare le résultat avec la solution */

void Sauvegarde(int ** grille_user,int **	IndicesColonnes,int ** IndicesLignes,Tcoup_t * TabCoup,int CompteurCoups,int width, int height,int n, int m, int essai);
/*Sauvegarde les coups du joueur, la grille du joueur et les indices de la grille et autres données dans une fichier Sauvegarde.txt*/

void Chargement(int ** grille_user,int ** IndicesColonnes,int ** IndicesLignes,Tcoup_t * TabCoup,int * PCompteurCoups,int * width, int * height, int * width_interface,int * width_grille, int * height_interface, int * height_grille, int * n, int * m, int * essai);
/*Recharge une sauvegarde de Sauvegarde.txt*/
#endif
