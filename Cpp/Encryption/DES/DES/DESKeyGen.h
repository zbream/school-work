#include "Common.h"

// Generate the DES 16 48-bit round keys, using the specified 64-bit key.
// Specify reverse as true for decryption, false for encryption.
void kg_generate(ull key64, ull keys48[16], bool reverse);