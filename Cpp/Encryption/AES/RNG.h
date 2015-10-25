#include "Common.h"

// Seed the random number generator using the current time.
void rng_seed();

// Pad the first (left) nBytes of block with random garbage.
void rng_padBlockWithGarbageL(uch block[16], uch nBytes);

// Pad the last (right) nBytes of block with random garbage.
void rng_padBlockWithGarbageR(uch block[16], uch nBytes);