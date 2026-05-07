#ifndef METRO_H
#define METRO_H

#include <stdio.h>
#include "random.h"
#include "config.h"

void update_metropolis(Lattice *lattice, const Params *parameters, Ran2Generator *rng);

#endif
