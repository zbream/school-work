#include "LinkLayer.h"
#include "PhysicalLayer.h"
#include <cstring>

// temporary contents of the 0/1 characters of a single byte
uch byteBuffer[8];

uint l_prepareFrame(uch charBuffer[CHAR_LIMIT], uint charN, uch frameBuffer[CHAR_LIMIT + 3])
{
	// total bytes in frame
	uint frameN = charN + 3;

	// create original frame data
	frameBuffer[0] = 22;
	frameBuffer[1] = 22;
	frameBuffer[2] = charN;
	memcpy(&frameBuffer[3], charBuffer, charN);

	// add parity
	for (uint i = 0; i < frameN; i++)
	{
		frameBuffer[i] = p_addParity(frameBuffer[i]);
	}

	return frameN;
}

uint l_prepareTransmission(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch transmissionBuffer[(CHAR_LIMIT + 3) * 8])
{
	uint transmissionN = 8 * frameN;

	for (uint i = 0; i < frameN; i++)
	{
		p_charToArray(frameBuffer[i], byteBuffer);
		memcpy(&transmissionBuffer[i * 8], byteBuffer, 8);
	}

	return transmissionN;
}

uint l_parseTransmission(uch transmissionBuffer[(CHAR_LIMIT + 3) * 8], uint transmissionN, uch frameBuffer[CHAR_LIMIT + 3])
{
	uint frameN = transmissionN / 8;

	// read frame data
	for (uint i = 0; i < frameN; i++)
	{
		frameBuffer[i] = p_arrayToChar(&transmissionBuffer[i * 8]);
	}

	return frameN;
}

uint l_parseFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch charBuffer[CHAR_LIMIT])
{
	// strip parity
	for (uint i = 0; i < frameN; i++)
	{
		frameBuffer[i] = p_stripParity(frameBuffer[i]);
	}

	// total chars in frame
	uint charN = frameBuffer[2];

	memcpy(charBuffer, &frameBuffer[3], charN);

	return charN;
}

bool l_validateFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN)
{
	for (uint i = 0; i < frameN; i++)
	{
		if (!p_checkParity(frameBuffer[i]))
		{
			return false;
		}
	}

	return true;
}