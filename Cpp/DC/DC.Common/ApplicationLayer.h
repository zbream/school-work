#include "Common.h"
#include <stdio.h>

/*
Read the next up-to-CHAR_LIMIT bytes from the specified file.
Returns the number of bytes read. */
uint a_readBuffer(FILE* file, uch charBuffer[CHAR_LIMIT]);

/*
Write the first charN bytes from the charBuffer to the specified file. */
void a_writeBuffer(FILE* file, uch charBuffer[CHAR_LIMIT], uint charN);