#include "Common.h"

// Seed the random number generator using the current time.
void rng_seed();

// Pad the left nBytes of block with random garbage.
// Returns the newly-padded block.
ull rng_padBlockWithGarbageL(ull block, ush nBytes);

// Pad the right nBytes of block with random garbage.
// Returns the newly-padded block.
ull rng_padBlockWithGarbageR(ull block, ush nBytes);
