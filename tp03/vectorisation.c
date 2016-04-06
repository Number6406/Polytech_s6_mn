#include <stdlib.h>
#include <limits.h>

#include <stdio.h>
#include <nmmintrin.h>
#include <xmmintrin.h>

#define N 1024
#define ITER 8000

typedef float float4 [4]  __attribute__ ((aligned (16))) ;
typedef short int int8 [8]   __attribute__ ((aligned (16))) ;

typedef float4 vectf[N];
typedef int8 vecti[N];

void print_vector_float (vectf T)
{
	int i;

	for(i=0; i<N; i++) {
		printf ("float : %2.4f %2.4f %2.4f %2.4f", T[i][0], T[i][1], T[i][2], T[i][3]) ;
	}

	printf("\n");
	return ;
}

void print_vector_int (vecti T)
{
	int i;

	for(i=0; i<N; i++) {
		printf ("int : %d %d %d %d %d %d %d %d", T[i][0], T[i][1], T[i][2], T[i][3], T[i][4], T[i][5], T[i][6], T[i][7]) ;
	}
	printf("\n");
	return ;
}

void initVf(vectf T) {
	int i;

	for(i=0; i<N; i++) {
		T[i][0] = 1.0;
		T[i][1] = 2.0;
		T[i][2] = 4.0;
		T[i][3] = 8.0;
	}
}

void initVi(vecti T) {
	int i;

	for(i=0; i<N; i++) {
		T[i][0] = 1;
		T[i][1] = 2;
		T[i][2] = 4;
		T[i][3] = 8;
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

	vecti iA ;
	vecti iB ;
	vecti iC ;

	__m128 v1, v2, v3 ;
	__m128i iV1, iV2, iV3 ;

	for(i=0; i<N; i++) {
		v1 = _mm_load_ps (a[i]) ;
		v2 = _mm_load_ps (b[i]) ;
		v3 = _mm_dp_ps (v1, v2, 0xFF) ;
		_mm_store_ps (c[i], v3) ;
		print_vector_float (c) ;
	}

	exit (0) ;
}
