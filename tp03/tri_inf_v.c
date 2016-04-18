#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution_v.c"

int main(int argc, char const *argv[]) {
	int i;
	
	for(i=0;i<ITER;i++){

		vectf X;
		vectf B;
		init_vectf(B);

		mat L;
		init_matInf(L);

		resolutionInf(L,B,X);
		
		#ifdef AFFICHAGE
		printf("A :\n"); aff_mat(L);
		printf("B : "); aff_vectf(B);
		printf("X :"); aff_vectf(X);	
		#endif
	}
	return 0;
}
