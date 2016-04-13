#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.h"

/**
 * Définition des différents types de matrices utilisés dans ce programme :
 * - Matrice diagonale
 * - Matrice triangulaire supérieure
 * - Matrice triangulaire inférieure
 */
// Pour une matrice diagonale on ne représente que les coefficients diagonaux
typedef float matd[N];
// Matrice triangulaire supérieure, allouée dynamiquement
typedef float* matU[N];
// Matrice triangulaire inférieure, allouée dynamiquement
typedef float* matL[N];

// Matrice quelconque
typedef float matrice[N][N];
// Vecteur
typedef float vect[N] ;


/** Fonction renvoyant un entier aléatoire*/
float rand_b(){
	return ((float) (rand()%((BORNESUP)-BORNEINF+1) + BORNEINF));
}
/**
 * Fonctions d'initialisation des matrices utilisées pour la résolution de systéme linéaire.
 */
 // Fonctions d'initialisation de matrice supérieure, aléatoirement
void init_matU (matU A) {
	register unsigned int i, j ;
	srand(time(NULL));
	for (i = 0; i < N; i++){
		A[i] = malloc(sizeof(float)*(N-(i+1)));
		for(j = 0; j < N-i; j++){
			A[i][j] = rand_b() ;
		}
	}
}


// Fonctions d'initialisation de matrice inférieure, aléatoirement
void init_matL (matL A) {
	register unsigned int i, j ;
	srand(time(NULL));
	for (i = 0; i < N; i++){
		A[i] = malloc(sizeof(float)*(i+1));
		for(j = 0; j <= i; j++){
			A[i][j] = rand_b() ;
		}
	}
}
// Fonction d'initialisation dematrice diagonale, aléatoirement
void init_matd (matd A) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    A [i] = rand_b();
}


// Fonction d'initialisation de vecteur, aléatoirement
void init_vect (vect V) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    V [i] = rand_b();
}

/**
 * Fonctions d'affichage
 */
// Fonctions d'affichage de matrices supérieures
void aff_matU (matU V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			if(j >= i){
				printf("|%4.1f",V[i][j-i]) ;
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

// Fonctions d'affichage de matrices inférieures
void aff_matL (matL V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			if(j <= i){
				printf("|%4.1f",V[i][j]) ;
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

// Fonctions d'affichage de matrices diagonales
void aff_matd(matd V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			if(j == i){
				printf("|%4.1f",V[i]) ;
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
void aff_vect (vect V){
	unsigned register int i;
	printf("[ %3.1f ",V[0]);
	for(i = 1; i < N; i++){
		printf("| %4.2f ",V[i]);
	}
	printf("]\n");
}


/**
 * Fonctions de résolution
 */
// Résolution de matrice diagonale
int res_d(matd A, vect B, vect X){
	register unsigned int i;

	for(i=0;i < N; i++){
		if(A[i]==0){
			if(B[i]!=0){
				fprintf(stderr,"Un coefficient est nul, pas de solution\n");
				return 1;
			} else
				fprintf(stderr,"Une infinité de solutions\n");
				return 2;
		}
		else X[i] = B[i]/A[i];
	}
	return 0;
}

// Résolution avec des matrices inférieures
void resolutionL (matL M, vect B, vect X) {
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

//Résolution avec des matrices supérieures
void resolutionU (matU M, vect B, vect X) {
	int i, j;

	X[N] = B[N] / M[N][N];
	for(i=N-1; i>=0; i--) {
		X[i] = B[i];
		for(j=i+1; j<N; j++) {
				X[i] -= (M[i][j]*B[j]);
		}
		X[i] = X[i] / M[i][i];
	}
}
