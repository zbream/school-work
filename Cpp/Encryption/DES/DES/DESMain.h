#include "Common.h"

void DESFileEncrypt(ull key, char inPath[], char outPath[]);
void DESFileDecrypt(ull key, char inPath[], char outPath[]);
ull DESBlock(ull[16], ull);