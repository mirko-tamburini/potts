#include "utils/config.h"
#include <stdio.h>

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

void initialize_lattice(Lattice *lattice, const Parameters *parameters, Ran2Generator *rng, FILE *pLatt) {
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
            pLatt = fopen("lattice", "r");
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

void read_parameters(Parameters *parameters, const char *filename){
      FILE *fp = fopen(filename, "rb");
      if (fp == NULL) {
            printf("Error: Unable to open the file %s.\n", filename);
            exit(1);
      }

      char line[256];
      char key[64];
      double val;

      while (fgets(line, sizeof(line), fp)) {
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
      fclose(fp);
}
