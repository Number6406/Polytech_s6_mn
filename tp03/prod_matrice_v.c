#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <smmintrin.h>

#include "resolution_v.c"


int main(int argc, char const *argv[]) {

  mat A, B, C;
  register unsigned int i, j;

  __m128 v1, v2, v3;

  init_matC(A);
  init_matC(B);

  for(i=0; i<N; i++) {
    for(j=0; j<N; j+=4) {
      v1 = _mm_load_ps (A[i]+j) ;
			v2 = _mm_load_ps (B[i]+j) ;

			v3 = _mm_dp_ps(v1,v2, 0xFF);

      C[i][j] += v3[0];
    }
  }

  printf("A :\n");
  aff_mat(A);
  printf("B :\n");
  aff_mat(B);

  printf("C :\n");
  aff_mat(C);

  return 0;
}
