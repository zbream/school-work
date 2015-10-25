#include "RNG.h"
#include <stdlib.h>
#include <time.h>

// NOTE: these random bytes are not truly randomly distributed,
// but are good enough to do what we need.
#define rngByte (rand() % 0x100)

void rng_seed()
{
	srand(time(NULL));
}

void rng_padBlockWithGarbageL(uch block[16], uch nBytes)
{
	for (int i = 0; i < nBytes; i++)
	{
		block[i] = rngByte;
	}
}

void rng_padBlockWithGarbageR(uch block[16], uch nBytes)
{
	for (int i = 0; i < nBytes; i++)
	{
		block[15 - i] = rngByte;
	}
}