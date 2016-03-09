#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

#define CUBE(X) (X)*(X)*(X)
/*
 * TP2 - Méthodes Numériques
 * 
 * ABONNENC Alicia
 * BONHOURE Gilles
 * RICM3
 * 
 * Le but de ce TP est de faire des multiplications sur des matrices.
 * Pour ce faire trois méthodes devront être employées :
 * 		- Parcours par lignes
 * 		- Parcours par colonnes
 * 		- Calcul par blocs de 32
 */


/* 
   mesure du temps
*/

static struct timeval _t1, _t2;
static struct timezone _tz;
static unsigned long _temps_residuel = 0;
unsigned long temps ;

#define top1() gettimeofday(&_t1, &_tz)
#define top2() gettimeofday(&_t2, &_tz)

#define ITER   20

void init_cpu_time(void)
{
   top1(); top2();
   _temps_residuel = 1000000L * _t2.tv_sec + _t2.tv_usec - 
                     (1000000L * _t1.tv_sec + _t1.tv_usec );
}

unsigned long cpu_time(void) /* retourne des microsecondes */
{
   return 1000000L * _t2.tv_sec + _t2.tv_usec - 
           (1000000L * _t1.tv_sec + _t1.tv_usec ) - _temps_residuel;
}

/*
	Définition des matrices
 */

#define N 400
#define BLOC 32

typedef float matrice_f[N][N];
typedef double matrice_d [N][N];

typedef float vect_f [N] ;

// Fonctions d'initialisations de matrices
void init_matf (matrice_f V, float value) {
  register unsigned int i, j ;
  for (i = 0; i < N; i++)
	for(j = 0; j < N; j++)
		V [i][j] = value+i ;
}

void init_matd (matrice_d V, double value) {
  register unsigned int i, j ;
  for (i = 0; i < N; i++)
	for(j = 0; j < N; j++)
		V [i][j] = value ;
}

// Fonction d'initialisation des vecteurs
void init_vect (vectfloat_t V, float value) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    V [i] = value ;
}

// Fonctions d'affichage de matrices
void aff_matf (matrice_f V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|-----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			printf("|%5.1f",V[i][j]) ;
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("|-----") ;
	}
	printf("|\n");
}

void aff_matd (matrice_d V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("|-----") ;
		}
		printf("|\n");
		for(j = 0; j < N; j++){
			printf("|%5.1f",V[i][j]) ;
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("|-----") ;
	}
	printf("|\n");
}

// Fonctions de calcul
/**
 * Vecteurs
 */
void addition_v(vect_f V1, vect_f V2, vect_f V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i++ ) {
		V[i] = V1[i] + V2[i];
	}
}


/**
 * Multiplications par les lignes
 */
void multLigneF (matrice_f x, matrice_f y, matrice_f mRes) {
	register unsigned int i, j, k;
	float somme;
	for(i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			somme = 0;
			for(k = 0; k < N; k++) {
				somme += (x[i][k] * y[k][j]);
			}
			mRes[i][j] = somme;
		}
	}
}

void multLigneF_OMP (matrice_f x, matrice_f y, matrice_f mRes) {
	register unsigned int i, j, k;
	float somme;
	
	#pragma omp parallel for private(i,j,k,somme)
	for(i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			somme = 0;
			for(k = 0; k < N; k++) {
				somme += (x[i][k] * y[k][j]);
			}
			mRes[i][j] = somme;
		}
	}
}

void multLigneD (matrice_d x, matrice_d y, matrice_d mRes) {
	register unsigned int i, j, k;
	double somme;
	for(i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			somme = 0;
			for(k = 0; k < N; k++) {
				somme += (x[i][k] * y[k][j]);
			}
			mRes[i][j] = somme;
		}
	}
}

/**
 * Multiplication par les colonnes
 */
void muxColonneF(matrice_f A, matrice_f B, matrice_f C){
	register unsigned int i, j, k;
	
	for(j = 0; j < N; j++){
		for(i = 0; i < N; i++){
			for(k=0; k < N; k++){
				C[i][j]=C[i][j]+A[i][k]*B[k][i];
			}
		}
	}
	
}

void muxColonneF_OMP(matrice_f A, matrice_f B, matrice_f C){
	register unsigned int i, j, k;
	
	#pragma omp parallel for private(i,j,k)
	for(j = 0; j < N; j++){
		for(i = 0; i < N; i++){
			for(k=0; k < N; k++){
				C[i][j]=C[i][j]+A[i][k]*B[k][i];
			}
		}
	}
	
}

/**
 * Multiplication par blocs
 */
void multBlocF(matrice_f A, matrice_f B, matrice_f C) {
	int block_i, block_j, local_i, local_j, k;
	float somme;
	for(block_i=0; block_i<(N/BLOC); block_i++) {
		for(block_j=0; block_j<(N/BLOC); block_j++) {
			for(local_i=block_i*BLOC; local_i<(block_i+1)*BLOC; local_i++) {
				for(local_j=block_j*BLOC; local_j<(block_j+1)*BLOC; local_j++) {
					somme = 0;
					for(k = 0; k < N; k++) {
						somme += (A[local_i][k] * B[k][local_j]);
					}
					C[local_i][local_j] = somme;						
				}
			}
		}
	}
}

void multBlocF_OMP(matrice_f A, matrice_f B, matrice_f C) {
	int block_i, block_j, local_i, local_j, k;
	float somme;
	
	#pragma omp parallel for private(block_i, block_j, k, local_i, local_j,somme)
	for(block_i=0; block_i<(N/BLOC); block_i++) {
		for(block_j=0; block_j<(N/BLOC); block_j++) {
			for(local_i=block_i*BLOC; local_i<(block_i+1)*BLOC; local_i++) {
				for(local_j=block_j*BLOC; local_j<(block_j+1)*BLOC; local_j++) {
					somme = 0;
					for(k = 0; k < N; k++) {
						somme += (A[local_i][k] * B[k][local_j]);
					}
					C[local_i][local_j] = somme;						
				}
			}
		}
	}
}

/**
 * Somme de matrices
 */
void sommeF(matrice_f A, matrice_f B, matrice_f C){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

/**
 * Multiplication MATRICExVECTEUR
 */
 void multVect(matrice_f A, vect_f V, vect_f Res){
	 
 }

// Définition des variables locales
matrice_f Af, Bf, Cf;
matrice_d Ad, Bd, Cd;
float flops;

int main(void){

	register unsigned int i;
	float flops;
  
	unsigned long temps ;
	
	init_matf(Af,2.0);
	init_matf(Bf,3.0);
	init_matf(Cf,0.0);
	
	init_matd(Ad,7.0);
	
	//aff_matf(Af);
	//aff_matd(Ad);
	//aff_matf(Cf);
	
	printf("Calculs sur %d matrices de dimension %d :\n", ITER, N);
	
	printf("// MULTIPLICATIONS //\n");
	/* Affichage du temps et des MFLOPS pour différents types d'opérations */
	printf("Multiplication | Lignes de la matrice de sortie\n");
	
	top1();
	for(i=0; i< ITER; i++)
		multLigneF(Af,Bf,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);


	printf("Multiplication OMP | Lignes de la matrice de sortie\n");
	top1();
	for(i=0; i< ITER; i++)
		multLigneF_OMP(Af,Bf,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	
	printf("Multiplication | Colonnes de la matrice de sortie\n");
	top1();
	for(i=0; i< ITER; i++)
		muxColonneF(Af,Af,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	
	printf("Multiplication OMP | Colonnes de la matrice de sortie\n");
	top1(); 
	for(i=0; i< ITER; i++)
		muxColonneF_OMP(Af,Af,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	
	printf("Multiplication | Par blocs de %d valeurs de la matrice de sortie\n",BLOC);
	top1();
	for(i=0; i< ITER; i++)
		multBlocF(Af,Bf,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	
	printf("Multiplication OMP | Par blocs de %d valeurs de la matrice de sortie\n",BLOC);
	top1();
	for(i=0; i< ITER; i++)
		multBlocF_OMP(Af,Bf,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(2*CUBE(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	
	printf("// SOMME //\n");
	top1();
	for(i=0; i< ITER; i++)
		sommeF(Af,Bf,Cf);
	top2();
	temps = cpu_time();
	
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)((N)*(N)) / (float)(temps * (1e-6)) *ITER;
	printf("MFLOPS : %f\n",flops/1e6);
	
	return 0;
}
