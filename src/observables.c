#include <math.h>
#include "observables.h"

void magnetization(Lattice *lattice, FILE *pOut) {
      double xmagn_real = 0.0;
      double xmagn_imag = 0.0;

      for(int i = 0; i < N_LATT; i++) {
            for(int j = 0; j < N_LATT; j++) {
                  double theta = 2.0 * PIGR * lattice->field[i][j] / 3.0;
                  xmagn_real += cos(theta);
                  xmagn_imag += sin(theta);
            }
      }
      xmagn_real /= N_VOL;
      xmagn_imag /= N_VOL;
      double magn_abs = sqrt(xmagn_real * xmagn_real + xmagn_imag * xmagn_imag);
      fprintf(pOut, "%lf %lf %lf ", xmagn_real, xmagn_imag, magn_abs);
}

void energy(Lattice *lattice, FILE *pOut) {
      double xene = 0.0;
      
      for(int i = 0; i < N_LATT; i++) {
            for(int j = 0; j < N_LATT; j++) {
                  int ip = lattice->npp[i];
                  int im = lattice->nmm[i];
                  int jp = lattice->npp[j];
                  int jm = lattice->nmm[j];

                  // Count how many nearest-neighbors have the same spin
                  int force = (lattice->field[i][j] == lattice->field[i][jp]) +
                              (lattice->field[i][j] == lattice->field[i][jm]) +
                              (lattice->field[i][j] == lattice->field[ip][j]) +
                              (lattice->field[i][j] == lattice->field[im][j]);

                  xene -= 0.5 * force;
            }
      }
      xene /= N_VOL;
      fprintf(pOut, "%lf\n", xene);
}