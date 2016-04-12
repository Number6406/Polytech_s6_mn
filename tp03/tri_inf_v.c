#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "resolution_v.c"

int main(int argc, char const *argv[]) {

	vectf X;
	vectf B;
	init_vectf(B);

	mat L;
	init_matInf(L);

	resolutionInf(L,B,X);

	printf("A :\n"); aff_mat(L);
	printf("B : "); aff_vectf(B);
	printf("X :"); aff_vectf(X);

	return 0;
}
