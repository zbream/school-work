#pragma once
#include "Common.h"

/*
Seed the random number generator using the current time. */
void rng_seed();

/*
Introduce an error at a 5% chance.
Returns true if we should introduce an error, false otherwise. */
bool rng_introduceError();