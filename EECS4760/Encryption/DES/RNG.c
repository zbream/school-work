#include "RNG.h"
#include <stdlib.h>
#include <time.h>

void rng_seed()
{
	srand(time(NULL));
}

ull rng_padBlockWithGarbageL(ull block, ush nBytes)
{
	// get nBytes random bytes
	ull random = rng_padBlockWithGarbageR(0, nBytes);

	// now shift these random bytes to align left
	random <<= (8 * (8 - nBytes));

	return (block | random);
}

ull rng_padBlockWithGarbageR(ull block, ush nBytes)
{
	// NOTE: these randon bytes are not truly randomly distributed, 
	// but are good enough to do what we need.

	// generate nBytes random bytes
	ull random = 0;
	for (ush i = 0; i < nBytes; i++)
	{
		random <<= 8;
		random |= (rand() % 0x100);
	}

	return (block | random);
}