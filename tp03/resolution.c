#include <stdio.h>
#include <stdlib.h>


#define N 20

/**
 * Définition des différents types de matrices utilisés dans ce programme :
 * - Matrice diagonale
 * - Matrice triangulaire supérieure
 * - Matrice triangulaire inférieure
 */
 // Pour une matrice diagonale on ne représente que les coefficients diagonaux
typedef int matd[N];

// Matrice quelconque
typedef float matrice[N][N];
// Vecteur
typedef float vect[N] ;

/**
 * Fonctions d'initialisation des matrices utilisées pour la résolution de systéme linéaire. 
 */
// Fonctions d'initialisations de matrice
void init_matf (matrice V, float value) {
  register unsigned int i, j ;
  for (i = 0; i < N; i++)
	for(j = 0; j < N; j++)
		V [i][j] = value+i ;
}

// Fonction d'initialisation des vecteurs
void init_vect (vect V, float value) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    V [i] = value ;
}

// Fonctions d'affichage de matrices
void aff_matf (matrice V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|-----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			printf("|%5.1f",V[i][j]) ;
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("|-----") ;
	}
	printf("|\n");
}


/**
 * Fonctions de résolution
 */

void res_d(matd A, vect B, vect X){
	register unsigned int i;
	
	for(i=0;i < N; i++){
		if(A[i]==0) fprintf(stderr,"Un coefficient est nul, pas de solution\n");
		X[i] = B[i]/A[i];
	}
}


int main(void){
	
	return 0;
}
