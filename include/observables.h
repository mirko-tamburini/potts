#ifndef OBSERVABLES_H
#define OBSERVABLES_H

#include <stdio.h>
#include "config.h"

typedef struct {
      double real;
      double img;
      double abs;
} Magn;

typedef double Ene;

Magn magnetization(Lattice *lattice);
Ene energy(Lattice *lattice);

#endif