#include <math.h>
#include "metro.h"

void update_metropolis(Lattice *lattice, const Parameters *parameters, Ran2Generator *rng) {
      int accepted_moves = 0;

      for(int ivol = 0; ivol < N_VOL; ivol++) {
            int i = (int) (ran2(rng) * N_LATT);
            int j = (int) (ran2(rng) * N_LATT);

            int ip = lattice->npp[i];
            int im = lattice->nmm[i];
            int jp = lattice->npp[j];
            int jm = lattice->nmm[j];

            // Count how many nearest-neighbors have the same spin
            int force = (lattice->field[i][j] == lattice->field[i][jp]) +
                        (lattice->field[i][j] == lattice->field[i][jm]) +
                        (lattice->field[i][j] == lattice->field[ip][j]) +
                        (lattice->field[i][j] == lattice->field[im][j]);

            double phi;       // spin test

            do {
                  int spin = (int) (3.0 * ran2(rng));  // Get 0, 1, or 2
                  phi = spin;
            } while(phi == lattice->field[i][j]);
            
            // Count how many nearest-neighbors have the same spin
            int force_test = (phi == lattice->field[i][jp]) +
                             (phi == lattice->field[i][jm]) +
                             (phi == lattice->field[ip][j]) +
                             (phi == lattice->field[im][j]);

            double p_rat = exp(parameters->beta * (force_test - force));
            double x = ran2(rng);
            
            if(x < p_rat) {
                  lattice->field[i][j] = phi;
                  accepted_moves++;
            }
      }
}