#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.c"

int main(void) {
	
	vect X;
	vect B;
	init_vect(B);
	
	printf("Matrice supérieure : \n");
	matU U;
	init_matU(U);
	#ifdef AFFICHAGE
	aff_matU(U);
	#endif
	
	printf("Résolution de matrice supérieure : AX = B\n");
	resolutionL(U,B,X);
	
	#ifdef AFFICHAGE
	printf("A :\n"); aff_matU(U);
	printf("B : "); aff_vect(B);
	printf("X :\n"); aff_vect(X);
	#endif
	
	return 0;
}
