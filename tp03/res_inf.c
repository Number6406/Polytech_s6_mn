#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.c"

int main(void) {

	vect X;
	vect B;
	//init_vect(B);
	B[0] = 2;
  B[1] = 3;
  B[2] = -7;


	printf("Matrice inférieure : \n");
	matL L;
	init_matL(L);
	L[0][0] = 2;
  L[1][0] = 4;
  L[1][1] = -1;
  L[2][0] = -6;
  L[2][1] = 1;
  L[2][2] = -2; 
	#ifdef AFFICHAGE
	aff_matL(L);
	#endif

	printf("Résolution de matrice inférieure : AX = B\n");
	resolutionL(L,B,X);
	#ifdef AFFICHAGE
	printf("A :\n"); aff_matL(L);
	printf("B : "); aff_vect(B);
	printf("X :\n"); aff_vect(X);
	#endif

	return 0;
}
