#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include "random.h"

#define N_LATT 10
#define N_VOL (N_LATT * N_LATT)

#define PIGR 3.14159265358979323846

typedef struct {
      int field[N_LATT][N_LATT];
      int npp[N_LATT], nmm[N_LATT];
} Lattice;

typedef struct {
      int iflag, measures, i_decorrel, i_term;
      double extfield, beta;
} Params;

void geometry(Lattice *lattice);
void initialize_lattice(Lattice *lattice, const Params *parameters, Ran2Generator *rng, const char *latt_file);
void read_parameters(Params *parameters, const char *params_file);

#endif