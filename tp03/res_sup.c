#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.c"

int main(void) {
<<<<<<< HEAD

	vect X;
	vect B;
	init_vect(B);
	B[2] = 2.0;

	printf("Matrice supérieure : \n");
	matU U;
	init_matU(U);
	U[2][0] = 1.0;
	#ifdef AFFICHAGE
	aff_matU(U);
	#endif

	printf("Résolution de matrice supérieure : AX = B\n");
	resolutionU(U,B,X);

	#ifdef AFFICHAGE
	printf("A :\n"); aff_matU(U);
	printf("B : "); aff_vect(B);
	printf("X :\n"); aff_vect(X);
	#endif

=======
	int i;
	vect B;
	init_vect(B);
	
	for(i=0;i<ITER;i++){
		vect X;
		//printf("Matrice supérieure : \n");
		matU U;
		init_matU(U);
		#ifdef AFFICHAGE
		aff_matU(U);
		#endif
		
		//printf("Résolution de matrice supérieure : AX = B\n");
		resolutionL(U,B,X);
		
		#ifdef AFFICHAGE
		printf("A :\n"); aff_matU(U);
		printf("B : "); aff_vect(B);
		printf("X :\n"); aff_vect(X);
		#endif
		
		sup_matU(U);
	}
>>>>>>> master
	return 0;
}
