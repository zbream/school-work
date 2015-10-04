#include "ApplicationLayer.h"

uch a_readBuffer(FILE* file, uch charBuffer[CHAR_LIMIT])
{
	char c;
	for (uch i = 0; i < CHAR_LIMIT; i++)
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

void a_writeBuffer(FILE* file, uch charBuffer[CHAR_LIMIT], uch charN)
{
	for (uch i = 0; i < charN; i++)
	{
		fputc(charBuffer[i], file);
	}
}