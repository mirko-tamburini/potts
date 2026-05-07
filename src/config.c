#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "config.h"

void geometry(Lattice *lattice) {
      /*
      npp and nmm are vectors of integers that take as input
      a coordinate and return the forward and backward
      coordinates, respectively, also taking into account the 
      periodic boundary conditions.
      */

      for(int i = 0; i < N_LATT; i++) {
            lattice->npp[i] = i + 1;
            lattice->nmm[i] = i - 1;
      }
      lattice->npp[N_LATT - 1] = 0;  // periodic boundary
      lattice->nmm[0] = N_LATT - 1;  // conditions
}

void initialize_lattice(Lattice *lattice, const Params *parameters, 
                        Ran2Generator *rng, const char *latt_file) {
      // COLD START -> the ground state is degenerate:
      //                            1) all spins = 0
      //                            2) all spins = 1
      //                            3) all spins = 2    
      // Here we select the second option for the ground state 

      if(parameters->iflag == 0) {
            for(int i = 0; i < N_LATT; i++) {
                  for(int j = 0; j < N_LATT; j++) {
                        lattice->field[i][j] = 1;
                  }
            }
      }

      // ... HOT START ... (random spins)
      else if(parameters->iflag == 1) {
            for(int i = 0; i < N_LATT; i++) {
                  for(int j = 0; j < N_LATT; j++) {
                        int spin = (int) (3.0 * ran2(rng));  // Get 0, 1, or 2
                        lattice->field[i][j] = spin;
                  }
            }
      }

      // ... or starting from the previous lattice configuration
      else {
            FILE *pLatt = fopen(latt_file, "r");
            if(pLatt == NULL) {
                  printf("Lattice file can't be found.\n");
                  return;
            }

            for(int i = 0; i < N_LATT; i++) {
                  for(int j = 0; j < N_LATT; j++) {
                        if(fscanf(pLatt, "%d", &(lattice->field[i][j])) != 1) {
                              printf("Error reading lattice file at site (%d, %d).\n", i, j);
                              fclose(pLatt);
                              return;
                        }
                  }
            }

            if(fscanf(pLatt, "%ld", &(rng->seed))) {
                  printf("Error reading seed.\n");
            }
            fclose(pLatt);
      }      
}

void read_parameters(Params *parameters, const char *params_file){
      FILE *pParams = fopen(params_file, "rb");
      if (pParams == NULL) {
            printf("Error: Unable to open the file %s.\n", params_file);
            exit(1);
      }

      char line[256];
      char key[64];
      double val;

      while (fgets(line, sizeof(line), pParams)) {
            // Skip comments or empty lines
            if (line[0] == '#' || line[0] == '\n') continue;

            // Parse key and value
            if (sscanf(line, "%s %lf", key, &val) == 2) {
                  if (strcmp(key, "iflag") == 0)      parameters->iflag = (int)val;
                  else if (strcmp(key, "measures") == 0)   parameters->measures = (int)val;
                  else if (strcmp(key, "i_decorrel") == 0) parameters->i_decorrel = (int)val;
                  else if (strcmp(key, "i_term") == 0)     parameters->i_term = (int)val;
                  else if (strcmp(key, "extfield") == 0)   parameters->extfield = val;
                  else if (strcmp(key, "beta") == 0)       parameters->beta = val;
            }
      }
      fclose(pParams);
}
