#include "LinkLayer.h"
#include "PhysicalLayer.h"
#include <cstring>

// temporary contents of the 0/1 characters of a single byte
uch byteBuffer[8];

uch l_prepareFrame(uch charBuffer[CHAR_LIMIT], uch charN, uch frameBuffer[3 + 8 * CHAR_LIMIT])
{
	// total bytes in frame
	uch frameN = 3 + 8 * charN;

	// create original frame data
	frameBuffer[0] = 22;
	frameBuffer[1] = 22;
	frameBuffer[2] = charN * 8;
	for (int i = 0; i < charN; i++)
	{
		p_charToArray(charBuffer[i], byteBuffer);
		memcpy(&frameBuffer[3 + 8 * i], byteBuffer, 8);
	}

	// add parity
	for (int i = 0; i < frameN; i++)
	{
		frameBuffer[i] = p_addParity(frameBuffer[i]);
	}

	return frameN;
}

uch l_parseFrame(uch frameBuffer[3 + 8 * CHAR_LIMIT], uch frameN, uch charBuffer[CHAR_LIMIT])
{
	// strip parity
	for (int i = 0; i < frameN; i++)
	{
		frameBuffer[i] = p_stripParity(frameBuffer[i]);
	}

	// total chars in frame
	uch charN = frameBuffer[2] / 8;

	// read frame data
	for (int i = 0; i < charN; i++)
	{
		charBuffer[i] = p_arrayToChar(&frameBuffer[3 + 8 * i]);
	}

	return charN;
}

bool l_validateFrame(uch frameBuffer[3 + 8 * CHAR_LIMIT], uch frameN)
{
	for (int i = 0; i < frameN; i++)
	{
		if (!p_checkParity(frameBuffer[i]))
		{
			return false;
		}
	}

	return true;
}