#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <smmintrin.h>

#define BORNEINF 0
#define BORNESUP 20
#define N 1024
#define ITER 1000

//Vectorisation de floats alignés sur 16 octets (4 float de 32 bits donc)
typedef float vectf [N]  __attribute__ ((aligned (16))) ;

//Type de matrice permettant de caractériser : et les matrice inf et les matrice sup
typedef vectf mat[N];


/** Fonction renvoyant un entier aléatoire compris entre BORNEINF et BORNESUP*/
float rand_b(){
	return ((float) (rand()%((BORNESUP)-BORNEINF+1) + BORNEINF));
}

/**
 * Fonctions d'initialisation des matrices utilisées pour la résolution de systéme linéaire.
 */
//Initialisation à 0.0 de toutes les cellules de la matrice
void init_mat(mat M) {
	register unsigned int i, j;
	for(i=0; i<N; i++) { //Boucle pour toutes les lignes
		for(j=0; j<N; j++) { //Pour toutes les colonnes
			M[i][j] = 0.0;
		}
	}
}

// Initialisation aléatoire pour une matrice carré (complète)
void init_matC(mat M) {
	register unsigned int i, j;
	srand(time(NULL));
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			M[i][j] = rand_b();
		}
	}
}

// Initialisation de matrice inférieure, aléatoirement
void init_matInf (mat M) {
	init_mat(M);
	register unsigned int i, j;
	srand(time(NULL));
	for (i=0; i < N; i++){
		for(j=0; j <= i; j++){
			M[i][j] = rand_b() ;
		}
	}
}

// Initialisation de matrice supérieure, aléatoirement
void init_matSup (mat M) {
 init_mat(M);
 register unsigned int i, j;
 srand(time(NULL));
 for (i=0; i < N; i++){
	 for(j=i; j<N; j++){
		 M[i][j] = rand_b() ;
	 }
 }
}

// Initialisation de vecteur, aléatoirement
void init_vectf (vectf V) {
  register unsigned int i ;
	srand(time(NULL));
  for (i = 0; i < N; i++)
    V [i] = rand_b();
}

/**
 * Fonctions d'affichage
 */
// Fonctions d'affichage de matrice
void aff_mat (mat M) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			printf("|%4.1f",M[i][j]) ;
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

// Résolution de matrices vectorisées inférieures
void resolutionInf (mat M, vectf B, vectf Res) {
	int i, j;
	int somme;

	__m128 v1, v2, v3, v4, v5; 

	for(i=0; i<N; i++) {
		somme = 0;
		for(j=0; j<i; j+=4) {
			v1 = _mm_load_ps (M[i]+j) ;
			v2 = _mm_load_ps (B+j) ;
			v3 = _mm_load_ps(Res+j);
      v4 = _mm_mul_ps(v1,v3);

			v5 = _mm_dp_ps(v4,v2, 0xFF);

			somme += v5[0];
		}

		Res[i] = (B[i]-somme) / M[i][i];
	}
}

// Résolution de matrices vectorisées supérieures
void resolutionSup (mat M, vectf B, vectf Res) {
	int i, j;
	int somme;

	__m128 v1, v2, v3;

	for(i=0; i<N; i++) {
		somme = 0;
		for(j=(i-i%4); j<N; j+=4) {
			v1 = _mm_load_ps (M[i]+j) ;
			v2 = _mm_load_ps (B+j) ;

			v3 = _mm_dp_ps(v1,v2, 0xFF);

			somme += v3[0];
		}

		Res[i] = somme / B[i];
	}
}
