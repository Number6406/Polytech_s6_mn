//gcc -msse4.1 -- compilation

#define BORNEINF 0
#define BORNESUP 20
#define AFFICHAGE

#define N 5

/**
 * Définition des différents types de matrices utilisés dans ce programme :
 * - Matrice diagonale
 * - Matrice triangulaire supérieure
 * - Matrice triangulaire inférieure
 */
// Pour une matrice diagonale on ne représente que les coefficients diagonaux
typedef float matd[N];
// Matrice triangulaire supérieure, allouée dynamiquement
typedef float* matU[N];
// Matrice triangulaire inférieure, allouée dynamiquement
typedef float* matL[N];
// Matrice quelconque
typedef float matrice[N][N];
// Vecteur
typedef float vect[N] ;


/** Fonction renvoyant un entier aléatoire*/
float rand_b();
/**
 * Fonctions d'initialisation des matrices utilisées pour la résolution de systéme linéaire.
 */
 // Fonctions d'initialisation de matrice supérieure
void init_matU (matU A);


// Fonctions d'initialisation de matrice inférieure
void init_matL (matL A);
// Fonction d'initialisation dematrice diagonale
void init_matd (matd A);
// Fonction d'initialisation de vecteur
void init_vect (vect V);


// Fonctions d'affichage de matrices supérieures
void aff_matU (matU V);
// Fonctions d'affichage de matrices inférieures
void aff_matL (matL V);
// Fonctions d'affichage de matrices diagonales
void aff_matd(matd V);
// Fonction d'affichage de vecteur
void aff_vect (vect V);


/**
 * Fonctions de résolution
 */
// Résolution de matrice diagonale
int res_d(matd A, vect B, vect X);
// Résolution avec des matrices inférieures
void resolutionL (matL M, vect B, vect X);
//Résolution avec des matrices supérieures
void resolutionU (matU M, vect B, vect X);
