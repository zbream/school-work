#include "Common.h"

// Perform 16 rounds of DES on the specified block, 
// using the specified 16 round keys in order.
// Returns the resulting block of the DES algorithm
ull r_runRounds(ull in, ull keys[16]);