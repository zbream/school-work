#include "Common.h"
#include <stdio.h>

// DES Encrypt the specified in file to the specified out file, 
// using the specified key.
void DESFileEncrypt(ull key, FILE* in, FILE* out);

// DES Decrypt the specified in file to the specified out file,
// using the specified key.
void DESFileDecrypt(ull key, FILE* in, FILE* out);