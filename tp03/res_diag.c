#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution.c"

int main(void){
	int i;
	vect B;
	init_vect(B);
	
	for(i=0;i<ITER;i++){
		
		vect X;
		
		//printf("Matrice diagonale : \n");
		matd D;
		init_matd(D);
		
		#ifdef AFFICHAGE
		aff_matd(D);
		#endif
		
		//printf("Résolution de matrice diagonale : AX = B\n");
		res_d(D,B,X);
		#ifdef AFFICHAGE
		printf("A :\n"); aff_matd(D);
		printf("B : "); aff_vect(B);
		printf("X :\n"); aff_vect(X);
		#endif
		
	}
	return 0;
}
