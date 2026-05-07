#include <math.h>
#include "observables.h"

Magn magnetization(Lattice *lattice) {
      Magn magn;

      double xmagn_real = 0.0;
      double xmagn_imag = 0.0;

      for(int i = 0; i < N_LATT; i++) {
            for(int j = 0; j < N_LATT; j++) {
                  double theta = 2.0 * PIGR * lattice->field[i][j] / 3.0;
                  xmagn_real += cos(theta);
                  xmagn_imag += sin(theta);
            }
      }
      magn.real = xmagn_real / N_VOL;
      magn.img = xmagn_imag / N_VOL;
      magn.abs = sqrt(pow(magn.real, 2.0) + pow(magn.img, 2.0));

      return magn;
}

Ene energy(Lattice *lattice) {
      Ene ene;

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
      ene = xene / N_VOL;

      return ene;
}