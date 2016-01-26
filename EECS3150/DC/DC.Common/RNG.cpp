#include "RNG.h"
#include <stdlib.h>
#include <time.h>

#define rngByte (rand() % 0x100)

void rng_seed()
{
	srand(time(NULL));
}

bool rng_introduceError()
{
	// introduce an error at a 5% chance
	// (rand() / RAND_MAX) < (5 / 100)
	return (rand() < (RAND_MAX * 5 / 100));
}