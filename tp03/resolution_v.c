#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef float vectf [N]  __attribute__ ((aligned (16))) ;

/**
 * Définition des différents types de matrices utilisés dans ce programme :
 * - Matrice diagonale
 * - Matrice
 */
// Matrice
typedef vectf mat[N];


/** Fonction renvoyant un entier aléatoire*/
float rand_b(){
	return ((float) (rand()%((BORNESUP)-BORNEINF+1) + BORNEINF));
}
/**
 * Fonctions d'initialisation des matrices utilisées pour la résolution de systéme linéaire.
 */
 // Fonctions d'initialisation de matrice, aléatoirement
void init_mat (mat M) {
	register unsigned int i, j;
	srand(time(NULL));
	for (i = 0; i < N; i++){
		for(j = 0; j < N-i; j++){
			M[i][j] = rand_b() ;
		}
	}
}

// Fonction d'initialisation de vecteur, et donc de matrice diagonale, aléatoirement
void init_vectf (vectf V) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    A [i] = rand_b();
}

/**
 * Fonctions d'affichage
 */
// Fonctions d'affichage de matrices supérieures
void aff_mat (mat M) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			if(j >= i){
				printf("|%4.1f",M[i][j-i]) ;
			} else {
				printf("|    ") ;
			}
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("|----") ;
	}
	printf("|\n");
}

// Fonction d'affichage de vecteur
void aff_vectf (vectf V){
	unsigned register int i;
	printf("[ %3.1f ",V[0]);
	for(i = 1; i < N; i++){
		printf("| %4.2f ",V[i]);
	}
	printf("]\n");
}

// Résolution de matrices vectorisées
void resolution (mat M, vectf B, vectf X) {
	int i, j;
	int somme;

	for(i=0; i<N; i++) {
		somme = 0;
		for(j=0; j<=i; j++) {
			somme += M[i][j];
		}

		X[i] = somme / B[i];
	}
}
