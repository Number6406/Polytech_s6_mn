#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

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

// Fonctions de calcul
matrice_f muxLigneF (matrice_f x, matrice_f y) {
	register unsigned int i, j;
	for (i = 0; i < N; i++)
		for(i = 0; j < N; j++)
}

// Définition des variables locales
matrice_f Af, Bf, Cf;
matrice_d Ad, Bd, Cd;

int main(void){
	
	init_matf(Af,2.0);
	init_matf(Bf,3.0);
	init_matf(Cf,0.0);
	
	top1();
	
	top2();
	
	return 0;
}
