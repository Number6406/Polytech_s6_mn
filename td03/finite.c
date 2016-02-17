#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>
#include <stdio.h>

#define N 1024
#define T 10000

/* 
   mesure du temps
*/

static struct timeval _t1, _t2;
static struct timezone _tz;
static unsigned long _temps_residuel = 0;

#define top1() gettimeofday(&_t1, &_tz)
#define top2() gettimeofday(&_t2, &_tz)

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

/* */

typedef float Vecteur [N] ;

void PrintVect (Vecteur v)
{
  unsigned int i ;

  for (i = 0; i < N; i++)
    printf ("%f ", v [i] ) ;
  printf ("\n") ;
  return ;
}

void ComputeStep (Vecteur XT, Vecteur XTP1)
{
  unsigned int i ;

  XTP1 [0] =  ((2 * XT [0]) + XT [1]) / 3 ;
  XTP1 [N-1] =  (XT [N-2] + (2 * XT [N-1])) / 3 ;
 
  for (i = 1; i < (N - 1); i++)
    {
      XTP1 [i] = (XT [i-1] + (2 * XT [i]) + XT [i+1]) / 4 ;
    }

  return ;
}

void ComputeTSteps (Vecteur X, Vecteur XT, int t)
{
  unsigned int i ;

  for (i = 0 ;  i < t; i++)
    {
      if ((i % 2) == 0)
	{
	  ComputeStep (X, XT);
	  //PrintVect (XT) ;
	}
      else
	{
	  ComputeStep (XT, X) ;
	  //PrintVect (X) ;
	}
    }
  if ((t % 2) == 0)
    {
      for (i = 0; i < N; i++)
		{
		  XT [i] = X [i] ;
		}
    }
}

void initVecteur(Vecteur V) {
	int i;
	for ( i = 0 ; i < N ; i++ )
		V[i] = (float) i ;
}

int main (int argc, char**argv)
{
	float flops;
	unsigned long temps;
	
	init_cpu_time () ;  
	
	Vecteur X0;
	initVecteur(X0);
	Vecteur X1 ;
	top1();
	ComputeTSteps (X0, X1, T) ;
	top2();
	PrintVect (X1) ;
	
	temps = cpu_time();
	printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
	flops = (float)(4*N-2) / (float)((temps * (1e-6))) * T;
	printf("MFLOPS : %f\n",flops/1e6);

}
