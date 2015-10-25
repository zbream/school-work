#include "Common.h"
#include <stdio.h>

void AESFileEncrypt(uch key[16], FILE* in, FILE* out);
void AESFileDecrypt(uch key[16], FILE* in, FILE* out);

void AESBlockEncrypt(uch keys[11][4][4], uch state[4][4]);
void AESBlockDecrypt(uch keys[11][4][4], uch state[4][4]);