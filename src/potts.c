
/* 
      NUMERICAL SIMULATION OF THE 3-STATE POTTS
            MODEL IN D=2 DIMENSIONS 
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "utils/random.h"
#include "utils/config.h"
#include "utils/metro.h"

int main() {
      clock_t start = clock();

      Lattice lattice;
      Parameters parameters;
      Ran2Generator rng;

      FILE *pOut;
      FILE *pLatt;

      const char *in_file = "parameters.json";
      const char *out_file = "measures";

      read_parameters(&parameters, in_file);

      ranstart(&rng);
      
      // OUTPUT FILE TO STORE THE MAGNETIZATION AND ENERGY
      pOut = fopen(out_file, "w"); 

      // PRELIMINARY OPERATIONS
      geometry(&lattice);
      initialize_lattice(&lattice, &parameters, &rng, pLatt);

      // THERMALIZATION
      for(int i = 0; i < parameters.i_term; i++) {
            update_metropolis(&lattice, &parameters, &rng);
      }

      // IN-EQUILIBRIUM SESSION WITH MEASURES
      for(int i = 0; i < parameters.measures; i++) {
            for(int j = 0; j < parameters.i_decorrel; j++) {
                  update_metropolis(&lattice, &parameters, &rng);
            }
            magnetization(&lattice, pOut);
            energy(&lattice, &parameters, pOut);
      }

      fclose(pOut);

      /*
      SAVING THE LATTICE CONFIGURATION AND RANDOM GENERATOR STATE
      TO POSSIBLY RESTART FROM THIS SITUATION
      */

      pLatt = fopen("lattice", "w");

      for(int i = 0; i < N_LATT; i++) {
            for(int j = 0; j < N_LATT; j++) {
                  fprintf(pLatt, "%d ", lattice.field[i][j]);
            }
            fprintf(pLatt, "\n");
      }

      fclose(pLatt);
      ranfinish(&rng);

      clock_t end = clock();
      double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("CPU execution time: %.0lf seconds", cpu_time);

      return EXIT_SUCCESS;
}
