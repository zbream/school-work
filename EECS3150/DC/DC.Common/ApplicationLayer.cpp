#include "ApplicationLayer.h"
#include <string>

char* ECString(EC ec)
{
	switch (ec)
	{
	case EC_CRC:
		return "CRC";
	case EC_HAMMING:
		return "Hamming";
	default:
		return "None";
	}
}

int a_findCommandLineSwitch(int switchc, char** switchv, const std::string& option, int nOptionParameters)
{
	int pos = std::find(switchv, switchv + switchc, option) - switchv;
	if (switchc - pos - 1 >= nOptionParameters)
	{
		return pos;
	}
	else
	{
		return -1;
	}
}

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