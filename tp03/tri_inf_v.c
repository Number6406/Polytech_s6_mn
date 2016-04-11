#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.c"

int main(void) {

	vect X;
	vect B;
	init_vect(B);

	printf("Matrice inférieure : \n");
	matL L;
	init_matL(L);
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
