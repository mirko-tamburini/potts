#ifndef OBSERVABLES_H
#define OBSERVABLES_H

#include "config.h"
#include <stdio.h>

void magnetization(Lattice *lattice, FILE *pOut);
void energy(Lattice *lattice, const Parameters *parameters, FILE *pOut);

#endif