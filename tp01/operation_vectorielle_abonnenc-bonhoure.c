#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

#include <stdio.h>

/*

Travailler sur des vecteurs qui tiennent dans le cache de
votre processeur et sur des vecteurs qui ne tiennent pas dans le cache
L3 de votre processeur. Sur des vecteurs qui ne tiennent pas dans le
cache, les performances devraient être inférieures.

Le calcul de la performance en FLOP (Floating Point Operation) par seconde.

Compiler avec gcc, sans option d'optimisation et avec option 
d'optimisation (O2, O3).

Calcule pour chaque opération le nombre d'opérations flottantes par seconde

Fournir un fichier README décrivant les résultats obtenus sur votre
processeur. Indiquer le type de processeur. Indiquer la taille des 
différents
niveaux de cache de votre processeur. Indiquer le compilateur utilisé
(gcc -v).

*/

/* 
   mesure du temps
*/

static struct timeval _t1, _t2;
static struct timezone _tz;
static unsigned long _temps_residuel = 0;

#define top1() gettimeofday(&_t1, &_tz)
#define top2() gettimeofday(&_t2, &_tz)


/*
   declaration du type vecteur 
*/

#define N      800000

typedef float vectfloat_t [N] ;

typedef double vectdouble [N] ;

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

// FONCTIONS D'INITIALISATION DES VECTEURS
void init_vect (vectfloat_t V, float value) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    V [i] = value ;
}

void init_vect_d (vectdouble V, double value) {
  register unsigned int i ;
  for (i = 0; i < N; i++)
    V [i] = value ;
}

// ADDITION
// Float
void addition_f1 (vectfloat_t V1, vectfloat_t V2, vectfloat_t V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i++ ) {
		V[i] = V1[i] + V2[i];
	}
}

void addition_f2 (vectfloat_t V1, vectfloat_t V2, vectfloat_t V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i+=8 ) {
		V[i] = V1[i] + V2[i];
		V[i+1] = V1[i+1] + V2[i+1];
		V[i+2] = V1[i+2] + V2[i+2];
		V[i+3] = V1[i+3] + V2[i+3];
		V[i+4] = V1[i+4] + V2[i+4];
		V[i+5] = V1[i+5] + V2[i+5];
		V[i+6] = V1[i+6] + V2[i+6];
		V[i+7] = V1[i+7] + V2[i+7];
	}
}
// Double
void addition_d1 (vectdouble V1, vectdouble V2, vectdouble V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i++ ) {
		V[i] = V1[i] + V2[i];
	}
}

void addition_d2 (vectdouble V1, vectdouble V2, vectdouble V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i+=8 ) {
		V[i] = V1[i] + V2[i];
		V[i+1] = V1[i+1] + V2[i+1];
		V[i+2] = V1[i+2] + V2[i+2];
		V[i+3] = V1[i+3] + V2[i+3];
		V[i+4] = V1[i+4] + V2[i+4];
		V[i+5] = V1[i+5] + V2[i+5];
		V[i+6] = V1[i+6] + V2[i+6];
		V[i+7] = V1[i+7] + V2[i+7];
	}
}

// MULTIPLICATION
//Float
void mult_f1 ( vectfloat_t V1, float k, vectfloat_t V) {
	
	register unsigned int i;
	
	for ( i=0 ; i < N ; i++ ){
		V[i] = V1[i] * k;
	}
	
}

void mult_f2 (vectfloat_t V1, float k, vectfloat_t V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i+=8 ) {
		V[i] = V1[i] * k;
		V[i+1] = V1[i+1] * k;
		V[i+2] = V1[i+2] * k;
		V[i+3] = V1[i+3] * k;
		V[i+4] = V1[i+4] * k;
		V[i+5] = V1[i+5] * k;
		V[i+6] = V1[i+6] * k;
		V[i+7] = V1[i+7] * k;
	}
	
}

// Double
void mult_d1 ( vectdouble V1, float k, vectdouble V) {
	register unsigned int i;
	
	for ( i=0 ; i < N ; i++ ){
		V[i] = V1[i] * k;
	}
	
}

void mult_d2 (vectdouble V1, float k, vectdouble V) {
	
	register unsigned int i ;
	
	for ( i = 0; i < N ; i+=8 ) {
		V[i] = V1[i] * k;
		V[i+1] = V1[i+1] * k;
		V[i+2] = V1[i+2] * k;
		V[i+3] = V1[i+3] * k;
		V[i+4] = V1[i+4] * k;
		V[i+5] = V1[i+5] * k;
		V[i+6] = V1[i+6] * k;
		V[i+7] = V1[i+7] * k;
	}
	
}

// PRODUIT SCALAIRE
// Float
float produit_scalaire_f1 (vectfloat_t V1, vectfloat_t V2) {
  register unsigned int i ;
  register float p = 0.0 ;

  for (i = 0 ; i < N; i++)
    {
      p = p + V1 [i] * V2 [i] ;
    }
    V1[0]=1.0;
    V2[0]=2.0;
  return p ;
}

float produit_scalaire_f2 (vectfloat_t V1, vectfloat_t V2) {
  register unsigned int i ;
  register float p = 0.0 ;

  for (i = 0 ; i < N; i=i+8)
    {
      p = p + V1 [i] * V2 [i] ;
      p = p + V1 [i+1] * V2 [i+1] ;
      p = p + V1 [i+2] * V2 [i+2] ;
      p = p + V1 [i+3] * V2 [i+3] ;
      p = p + V1 [i+4] * V2 [i+4] ;
      p = p + V1 [i+5] * V2 [i+5] ;
      p = p + V1 [i+6] * V2 [i+6] ;
      p = p + V1 [i+7] * V2 [i+7] ;
    }
    V1[0]=1.0;
    V2[0]=2.0;
  return p ;
}

// Double
double produit_scalaire_d1 (vectdouble V1, vectdouble V2) {
  register unsigned int i ;
  register double p = 0.0 ;

  for (i = 0 ; i < N; i++)
    {
      p = p + V1 [i] * V2 [i] ;
    }
    V1[0]=1.0;
    V2[0]=2.0;
  return p ;
}

double produit_scalaire_d2 (vectdouble V1, vectdouble V2) {
  register unsigned int i ;
  register double p = 0.0 ;

  for (i = 0 ; i < N; i=i+8)
    {
      p = p + V1 [i] * V2 [i] ;
      p = p + V1 [i+1] * V2 [i+1] ;
      p = p + V1 [i+2] * V2 [i+2] ;
      p = p + V1 [i+3] * V2 [i+3] ;
      p = p + V1 [i+4] * V2 [i+4] ;
      p = p + V1 [i+5] * V2 [i+5] ;
      p = p + V1 [i+6] * V2 [i+6] ;
      p = p + V1 [i+7] * V2 [i+7] ;
    }
    V1[0]=1.0;
    V2[0]=2.0;
  return p ;
}

/**************************************
        PROGRAMME PRINCIPAL
***************************************/ 

  vectfloat_t Vect1, Vect2, v ;
  vectdouble VectD1, VectD2, V2;
  
int main (int argc, char **argv) {

  float ps ;
  double ps_d;
  register unsigned int i ;
  float flops;
  
  unsigned long temps ;
  
  float k;
  k = 9.75;
  
  init_vect (Vect1, 1.0) ;
  init_vect (Vect2, 2.0) ;
    
  init_vect_d (VectD1, 1.0) ;
  init_vect_d (VectD2, 2.0) ;

  init_cpu_time();
    
 // TESTS des opérations codées   

  // Additions
  // Floats
  top1 () ;
    for (i=0; i < ITER; i++)
      { addition_f1 (Vect1, Vect2, v) ; }
  top2 () ;
  
  printf ("Addition float 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  top1 () ;
    for (i=0; i < ITER; i++)
      { addition_f2 (Vect1, Vect2, v) ; }
  top2 () ;
  
  printf ("Addition float 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  //Doubles
  top1 () ;
    for (i=0; i < ITER; i++)
      { addition_d1 (VectD1, VectD2, V2) ; }
  top2 () ;
  
  printf ("Addition double 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  top1 () ;
    for (i=0; i < ITER; i++)
      { addition_d2 (VectD1, VectD2, V2) ; }
  top2 () ;
  
  printf ("Addition double 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);

  // Multiplications
  // Floats
  top1 () ;
    for (i=0; i < ITER; i++)
      {	mult_f1 (Vect1, k, v) ; }
  top2 () ;
  
  printf ("Mult float 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  top1 () ;
    for (i=0; i < ITER; i++)
      { mult_f2 (Vect1, k, v) ; }
  top2 () ;
  
  printf ("Mult float 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  //Doubles
  top1 () ;
    for (i=0; i < ITER; i++)
      { mult_d1 (VectD1, k, V2) ; }
  top2 () ;
  
  printf ("Mult double 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  top1 () ;
    for (i=0; i < ITER; i++)
      { mult_d2 (VectD1, k, V2) ; }
  top2 () ;
  
  printf ("Mult double 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  // Produit Scalaire
  // Float
  top1();
	for (i=0; i < ITER; i++)
      { ps = produit_scalaire_f1 (Vect1,Vect2); }
  top2 () ; 
  
  printf ("Produit scalaire float 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(2.0 * N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  top1();
	for (i=0; i < ITER; i++)
      { ps = produit_scalaire_f2 (Vect1,Vect2); }
  top2 () ; 
  
  printf ("Produit scalaire float 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(2.0 * N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
  
  // Double
  top1();
	for (i=0; i < ITER; i++)
      { ps_d = produit_scalaire_d1 (VectD1,VectD2); }
  top2 () ; 
  
  printf ("Produit scalaire double 1 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(2.0 * N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
 
 
  top1();
	for (i=0; i < ITER; i++)
      { ps_d = produit_scalaire_d2 (VectD1,VectD2); }
  top2 () ; 
  
  printf ("Produit scalaire double 2 : ") ;
  temps = cpu_time () ;
  printf("time = %ld.%03ldms\n", temps/1000, temps%1000);
  flops = (float)(2.0 * N) / (float)((temps * (1e-6))) * ITER;
  printf("MFLOPS : %f\n",flops/1e6);
 
  return 0;
}
