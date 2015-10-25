#include "Common.h"

// Generate the AES 10 16-byte round keys, using the specified 16-byte user key.
// Populates keys[1] through keys[10] with round keys, keys[0] is the user key.
void kg_generate(uch userKey[16], uch keys[11][4][4]);