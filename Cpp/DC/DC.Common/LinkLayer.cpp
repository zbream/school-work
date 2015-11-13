#include "LinkLayer.h"
#include "PhysicalLayer.h"
#include "RNG.h"
#include <cstring>

// temporary contents of the 0/1 characters of a single byte
uch byteBuffer[8];
uch hammingBuffer[12];

void l_addCharParity(uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_addParity(charBuffer[i]);
	}
}

bool l_validateCharParity(uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		if (!p_checkParity(charBuffer[i]))
		{
			return false;
		}
	}

	return true;
}

void l_stripCharParity(uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_stripParity(charBuffer[i]);
	}
}

uint l_prepareData(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT])
{
	// total bits in data
	uint dataN = charN * 8;

	// convert bytes to 0/1 chars
	for (uint i = 0; i < charN; i++)
	{
		p_charToArray(charBuffer[i], byteBuffer);
		memcpy(&dataBuffer[i * 8], byteBuffer, 8);
	}

	return dataN;
}

uint l_parseData(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT])
{
	// total bytes in data
	uint charN = dataN / 8;

	// read chars from data
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_arrayToChar(&dataBuffer[i * 8]);
	}

	return charN;
}

uint l_prepareDataCrc(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT])
{
	// total bits in data
	uint dataN = charN * 8;

	// convert bytes to 0/1 chars
	for (uint i = 0; i < charN; i++)
	{
		p_charToArray(charBuffer[i], byteBuffer);
		memcpy(&dataBuffer[i * 8], byteBuffer, 8);
	}

	// augment spaces for CRC remainder to dataBuffer
	memset(&(dataBuffer[dataN]), '0', 16);
	dataN += 16;

	// add CRC remainder to dataBuffer
	uint crc = p_crcAnsi(dataBuffer, dataN);
	for (int i = 0; i < 16; i++)
	{
		uch bit = ((crc & 0x1) ? '1' : '0');
		crc >>= 1;

		dataBuffer[dataN - 1 - i] = bit;
	}

	return dataN;
}

bool l_validateDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN)
{
	uint crc = p_crcAnsi(dataBuffer, dataN);
	return (crc == 0);
}

uint l_parseDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT])
{
	// total bytes in data (minus the CRC)
	uint charN = (dataN / 8) - 2;

	// read chars from data
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_arrayToChar(&dataBuffer[i * 8]);
	}
	
	return charN;
}

uint l_prepareDataHamming(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT])
{
	// total bits in data
	uint dataN = charN * 12;

	// convert bytes to 0/1 chars, hamming encoded
	for (uint i = 0; i < charN; i++)
	{
		p_hammingCharTo12(charBuffer[i], hammingBuffer);
		memcpy(&dataBuffer[i * 12], hammingBuffer, 12);
	}

	return dataN;
}

uint l_parseDataHamming(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT])
{
	// total bytes in data
	uch charN = dataN / 12;

	// read chars from data
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_hamming12ToChar(&dataBuffer[i * 12]);
	}

	return charN;
}

#define flipChar(character) ((character) == '1' ? '0' : '1')

int l_introduceErrors(uch dataBuffer[DATA_LIMIT], uint dataN, int maxErrors, int errorPos[])
{
	int errors = 0;

	for (uint i = 0; i < dataN; i++)
	{
		if (errors == maxErrors) break;
		
		if (rng_introduceError())
		{
			// flip the bit, record which bit we flipped
			dataBuffer[i] = flipChar(dataBuffer[i]);
			errorPos[errors++] = i;
		}
	}

	return errors;
}