#include "Common.h"
#include <stdio.h>

// AES Encrypt the specified in file to the specified out file,
// using the specified 16-byte key.
void AESFileEncrypt(uch key[16], FILE* in, FILE* out);

// AES Decrypt the specified in file to the specified out file,
// using the specified 16-byte key.
void AESFileDecrypt(uch key[16], FILE* in, FILE* out);