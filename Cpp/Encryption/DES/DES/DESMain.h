#include "Common.h"
#include <stdio.h>

void DESFileEncrypt(ull key, FILE* in, FILE* out);
void DESFileDecrypt(ull key, FILE* in, FILE* out);
ull DESBlock(ull[16], ull);