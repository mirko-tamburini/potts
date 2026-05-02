/*
      This snippet defines the RAN2 
      generator for C code.
*/

#include "utils/random.h"
#include <stdio.h>

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

void ranstart(Ran2Generator *rng) {
      FILE *pSeed;
      pSeed = fopen("randomseed", "r");

      if(pSeed == NULL) {
            printf("Missing seed file.\n");
            return;
      }
      /*
      If the file "randomseed" doesn't exist, you have to create it and
      set the default value for idum, which is expected to be a negative number.
      */
      if(fscanf(pSeed, "%ld", &(rng->idum)) != 1) {
            printf("Error reading idum. Use the default seed: idum = -1\n");
            fclose(pSeed);
            return;
      }
      if(fscanf(pSeed, "%ld", &(rng->idum2)) != 1) {
            printf("No idum2 found. Initializating to default value.\n");
            rng->idum2 = 123456789;
            fclose(pSeed);
            return;
      }
      for(int i = 0; i < NTAB; i++) {
           if(fscanf(pSeed, "%ld", &(rng->iv[i])) != 1) {
                  printf("No iv[%d] found. Initializating to default value.\n", i);
                  rng->iv[i] = 0;
                  fclose(pSeed);
                  return;
           } 
      }
      if(fscanf(pSeed, "%ld", &(rng->iy)) != 1) {
            printf("No iy found. Initializating to default value.\n");
            rng->iy = 0;
            fclose(pSeed);
            return;
      }
      if(rng->idum >= 0) {
            rng->idum = - rng->idum - 1;
      }
      fclose(pSeed);
}

void ranfinish(Ran2Generator *rng) {
      FILE *pSeed;
      pSeed = fopen("randomseed", "w");

      fprintf(pSeed, "%ld\n", rng->idum);
      fprintf(pSeed, "%ld\n", rng->idum2);

      for(int i = 0; i < NTAB; i++) {
            fprintf(pSeed, "%ld\n", rng->iv[i]);
      }
      
      fprintf(pSeed, "%ld\n", rng->iy);
      fclose(pSeed);
}

/*
----------------------------------------------------------------------
      RANDOM NUMBER GENERATOR: standard ran2 from numerical recipes
----------------------------------------------------------------------
*/
double ran2(Ran2Generator *rng)
/*   ACHTUNG!! 
La funzione originale trovata in Numerical Recipes prende come parametro
d'ingresso long *idum. Nel codice, invece, vengono passati come parametri
d'ingresso il puntatore dell'intera struttura Ran2Generator, i cui valori
idum, idum2, iv[NTAB], iy verranno opportunamente aggiornati nella funzione.

Long period (> 2 × 1018) random number generator of L’Ecuyer with Bays-Durham shuffle
and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of
the endpoint values). Call with idum a negative integer to initialize; thereafter, do not alter
idum between successive deviates in a sequence. RNMX should approximate the largest floating
value that is less than 1.
*/
{
      int j;
      long k;
      // static long idum2=123456789;
      // static long iy=0;
      // static long iv[NTAB];
      double temp;
      if (rng->idum <= 0) {
      if (-(rng->idum) < 1) rng->idum = 1;
      else rng->idum = - (rng->idum);
      rng->idum2 = (rng->idum);
      for (j = NTAB + 7; j >= 0; j--) {
      k = (rng->idum) / IQ1;
      rng->idum = IA1 * (rng->idum - k * IQ1)- k * IR1;
      if (rng->idum < 0) rng->idum += IM1;
      if (j < NTAB) rng->iv[j] = rng->idum;
      }
      rng->iy = rng->iv[0];
      }
      k = (rng->idum) / IQ1;
      rng->idum = IA1 * (rng->idum - k * IQ1) - k * IR1;
      if (rng->idum < 0) rng->idum += IM1;
      k = rng->idum2 / IQ2;
      rng->idum2 = IA2 * (rng->idum2 - k * IQ2) - k * IR2;
      if (rng->idum2 < 0) rng->idum2 += IM2;
      j = rng->iy / NDIV;
      rng->iy = rng->iv[j] - rng->idum2;
      rng->iv[j] = rng->idum;
      if (rng->iy < 1) rng->iy += IMM1;
      /*
      Initialize.
      Be sure to prevent idum =0.
      Load the shuffle table (after 8 warm-ups).
      Start here when not initializing.
      Compute idum=(IA1*idum) % IM1 without
      overflows by Schrage’s method.
      Compute idum2=(IA2*idum) % IM2 likewise.
      Will be in the range 0..NTAB-1.
      Here idum is shuffled, idum and idum2 are
      combined to generate output.
      */
      if ((temp = AM * rng->iy) > RNMX) return RNMX; //Because users don’t expect endpoint values.
      else return temp;
}