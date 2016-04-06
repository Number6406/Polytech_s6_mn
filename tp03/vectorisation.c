#include <stdlib.h>
#include <limits.h>

#include <stdio.h>
#include <nmmintrin.h>
#include <xmmintrin.h>

#define N 8
#define ITER 8000

typedef float vectf [N]  __attribute__ ((aligned (16))) ;

void print_vector_float (vectf T)
{
	int i;

	for(i=0; i<N; i++) {
		printf ("float : %f", T[i]) ;
	}

	printf("\n");
	return ;
}

void initVf(vectf T) {
	int i;

	for(i=0; i<N; i++) {
		T[i] = 1.0;
	}
}

int main (int argc, char **argv)
{

	int i;

	vectf a ; initVf(a);
	vectf b ; initVf(b);
	vectf c ;

	print_vector_float(a);

	printf("================================================\n");

	print_vector_float(b);

	printf("================================================\n");

	__m128 v1, v2, v3 ;
	__m128i iV1, iV2, iV3 ;

	for(i=0; i<N; i+=4) {
		v1 = _mm_load_ps (a+i) ;
		v2 = _mm_load_ps (b+i) ;
		v3 = _mm_dp_ps (v1, v2, 0xFF) ;
		_mm_store_ps (c+i, v3) ;
	}
	print_vector_float (c) ;

	exit (0) ;
}
