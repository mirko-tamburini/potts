#ifndef RANDOM_H
#define RANDOM_H

#define NTAB 32

typedef struct {
    long idum, idum2, iv[NTAB], iy, seed;
} Ran2Generator;

// Function prototypes
void ranstart(Ran2Generator *rng, const char *seed_file);
void ranfinish(Ran2Generator *rng, const char *seed_file);
double ran2(Ran2Generator *rng);

#endif