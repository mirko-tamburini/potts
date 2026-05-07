
/* 
      NUMERICAL SIMULATION OF THE 3-STATE POTTS
            MODEL IN D=2 DIMENSIONS 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "random.h"
#include "config.h"
#include "metro.h"
#include "observables.h"

int main() {
      clock_t start = clock();

      Lattice lattice;
      Params params;
      Ran2Generator rng;

      const char *params_file = "input/params.dat";
      const char *seed_file = "input/randomseed";
      const char *meas_file = "output/measures.dat";
      const char *latt_file = "output/lattice.dat";

      read_parameters(&params, params_file);

      ranstart(&rng, seed_file);
      
      // OUTPUT FILE TO STORE THE MAGNETIZATION AND ENERGY DENSITY
      FILE *pMeas = fopen(meas_file, "w"); 
      fprintf(pMeas, "%s %s %s\t %s\t %s\t %s\n", "#", "Step", "Magn_Real", "Magn_Img", "Magn_Abs", "Ene");

      // PRELIMINARY OPERATIONS
      geometry(&lattice);
      initialize_lattice(&lattice, &params, &rng, latt_file);

      // THERMALIZATION
      int MC_step = 0;
      for(int i = 0; i < params.i_term; i++) {
            update_metropolis(&lattice, &params, &rng);
            MC_step++;
      }

      // IN-EQUILIBRIUM SESSION WITH MEASURES
      Magn magn;
      Ene ene;

      for(int i = 0; i < params.measures; i++) {
            for(int j = 0; j < params.i_decorrel; j++) {
                  update_metropolis(&lattice, &params, &rng);
                  MC_step++;
            }
            magn = magnetization(&lattice);
            ene = energy(&lattice);
            fprintf(pMeas, "%d\t %lf\t %lf\t %lf\t %lf\n", MC_step, magn.real, magn.img, magn.abs, ene);
      }

      fclose(pMeas);

      /*
      SAVING THE LATTICE CONFIGURATION AND RANDOM GENERATOR STATE
      TO POSSIBLY RESTART FROM THIS SITUATION
      */

      FILE *pLatt = fopen(latt_file, "w");

      for(int i = 0; i < N_LATT; i++) {
            for(int j = 0; j < N_LATT; j++) {
                  fprintf(pLatt, "%d ", lattice.field[i][j]);
            }
            fprintf(pLatt, "\n");
      }
      fclose(pLatt);

      ranfinish(&rng, seed_file);

      clock_t end = clock();
      double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("CPU execution time: %.0lf seconds", cpu_time);

      return EXIT_SUCCESS;
}
