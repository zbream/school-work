#include "ApplicationLayer.h"

uint a_readBuffer(FILE* file, uch charBuffer[CHAR_LIMIT])
{
	char c;
	for (uint i = 0; i < CHAR_LIMIT; i++)
	{
		c = fgetc(file);
		if (c != EOF)
		{
			charBuffer[i] = c;
		}
		else
		{
			return i;
		}
	}

	return CHAR_LIMIT;
}

void a_writeBuffer(FILE* file, uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		fputc(charBuffer[i], file);
	}
}