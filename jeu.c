#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"

int * IndiceLignes(int n,int m,int ** grille) {
    int i=0;
    int j=0;
    int indice=0;
    int indicelign[n];
    int compteur=0;

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
    int i=0;
    int j=0;
    int indice=0;
    int indicecol[m];
    int compteur=0;

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
