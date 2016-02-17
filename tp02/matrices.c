#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>


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

#define top1() gettimeofday(&_t1, &_tz)
#define top2() gettimeofday(&_t2, &_tz)

#define ITER   2000

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

#define N 10

typedef float matrice_f[N][N];
typedef double matrice_d [N][N];

// Fonctions d'initialisations de matrices
void init_matf (matrice_f V, float value) {
  register unsigned int i, j ;
  for (i = 0; i < N; i++)
	for(j = 0; j < N; j++)
		V [i][j] = value ;
}

void init_matd (matrice_d V, double value) {
  register unsigned int i, j ;
  for (i = 0; i < N; i++)
	for(j = 0; j < N; j++)
		V [i][j] = value ;
}

// Fonctions d'affichage de matrices
void aff_matf (matrice_f V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("----") ;
		}
		printf("-\n");
		for(j = 0; j < N; j++){
			printf("|%.1f",V[i][j]) ;
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("----") ;
	}
	printf("-\n");	
}

void aff_matd (matrice_d V) {
	register unsigned int i, j ;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("----") ;
		}
		printf("-\n");
		for(j = 0; j < N; j++){
			printf("|%.1f",V[i][j]) ;
		}
		printf("|\n");
	}
	for(j = 0; j < N; j++){
		printf("----") ;
	}
	printf("-\n");	
}

// Fonctions de calcul
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

// Définition des variables locales
matrice_f Af, Bf, Cf;
matrice_d Ad, Bd, Cd;

int main(void){
	
	init_matf(Af,2.0);
	init_matf(Bf,3.0);
	init_matf(Cf,0.0);
	
	init_matd(Ad,7.0);
	
	aff_matf(Af);
	aff_matd(Ad);
	top1();
	multLigneF(Af,Bf,Cf);
	top2();
	aff_matf(Cf);
	
	return 0;
}
