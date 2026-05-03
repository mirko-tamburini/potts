#ifndef OBSERVABLES_H
#define OBSERVABLES_H

#include <stdio.h>
#include "config.h"

void magnetization(Lattice *lattice, FILE *pOut);
void energy(Lattice *lattice, FILE *pOut);

#endif