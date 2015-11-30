#include "LinkLayer.h"
#include "PhysicalLayer.h"
#include "RNG.h"
#include <cstring>

// temporary contents of the 0/1 characters of a single byte
uch byteBuffer[8];
uch hammingBuffer[12];

// temporary contents of 4 characters in HDB3
uch hdb3Buffer[4];

void l_addCharParity(uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_addParity(charBuffer[i]);
	}
}

bool l_validateCharParity(uch charBuffer[CHAR_LIMIT], uint charN, bool charBufferParity[CHAR_LIMIT])
{
	bool valid = true;

	for (uint i = 0; i < charN; i++)
	{
		if (!(charBufferParity[i] = p_checkParity(charBuffer[i])))
		{
			valid = false;
		}
	}

	return valid;
}

void l_stripCharParity(uch charBuffer[CHAR_LIMIT], uint charN)
{
	for (uint i = 0; i < charN; i++)
	{
		charBuffer[i] = p_stripParity(charBuffer[i]);
	}
}

void l_prepareFrameHeader(uch transmitBuffer[TRANSMIT_LIMIT], uint charN)
{
	transmitBuffer[0] = transmitBuffer[1] = 0x22;
	transmitBuffer[2] = charN;
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

int l_introduceErrors(uch dataBuffer[DATA_LIMIT], uint dataN, int maxErrors, int errorPos[])
{
	int errors = 0;

	for (uint i = 0; i < dataN; i++)
	{
		if (errors == maxErrors) break;
		
		if (rng_introduceError())
		{
			// flip the bit, record which bit we flipped
			dataBuffer[i] = (dataBuffer[i] == '1' ? '0' : '1');
			errorPos[errors++] = i;
		}
	}

	return errors;
}

void l_encodeHdb3(uch dataBuffer[DATA_LIMIT], uint dataN)
{
	bool evenParity = true;
	bool previousPulseHI = false;

	int i = 0;
	while (i < dataN)
	{
		// get next 4 characters
		int remaining = dataN - i;
		if (remaining >= 4)
		{
			memcpy(hdb3Buffer, &dataBuffer[i], 4);
		}
		else
		{
			memcpy(hdb3Buffer, &dataBuffer[i], remaining);
			memcpy(hdb3Buffer + remaining, "222", 4 - remaining);
		}

		// check for 0000
		if (!strncmp((char*)hdb3Buffer, "0000", 4))
		{
			// 0000, encode

			if (evenParity)
			{
				if (previousPulseHI)
				{
					// -00-
					memcpy(&dataBuffer[i], "-00-", 4);
				}
				else
				{
					// +00+
					memcpy(&dataBuffer[i], "+00+", 4);
				}
			}
			else
			{
				if (previousPulseHI)
				{
					// 000+
					memcpy(&dataBuffer[i], "000+", 4);
				}
				else
				{
					// 000-
					memcpy(&dataBuffer[i], "000-", 4);
				}
			}

			evenParity = true;
			i += 4;
		}
		else
		{
			// not 0000, encode just the first bit
			uch c = hdb3Buffer[0];

			if (c == '0')
			{
				dataBuffer[i] = '0';
			}
			else
			{
				dataBuffer[i] = (previousPulseHI ? '-' : '+');
				previousPulseHI = !previousPulseHI;
				evenParity = !evenParity;
			}

			++i;
		}
	}
}

void l_decodeHdb3(uch dataBuffer[DATA_LIMIT], uint dataN)
{
	bool evenParity = true;
	bool previousPulseHI = false;

	int i = 0;
	while (i < dataN)
	{
		// get next 4 characters
		int remaining = dataN - i;
		if (remaining >= 4)
		{
			memcpy(hdb3Buffer, &dataBuffer[i], 4);
		}
		else
		{
			memcpy(hdb3Buffer, &dataBuffer[i], remaining);
			memcpy(hdb3Buffer + remaining, "222", 4 - remaining);
		}

		// check for 0000 pattern
		if ((!strncmp((char*)hdb3Buffer, "000+", 4) && !evenParity && previousPulseHI)
			|| (!strncmp((char*)hdb3Buffer, "000-", 4) && !evenParity && !previousPulseHI)
			|| (!strncmp((char*)hdb3Buffer, "-00-", 4) && evenParity && previousPulseHI)
			|| (!strncmp((char*)hdb3Buffer, "+00+", 4) && evenParity && !previousPulseHI))
		{
			// 0000, decode
			memcpy(&dataBuffer[i], "0000", 4);

			evenParity = true;
			i += 4;
		}
		else
		{
			// not 0000, decode just the first bit
			if (hdb3Buffer[0] == '0')
			{
				dataBuffer[i] = '0';
			}
			else
			{
				dataBuffer[i] = '1';
				previousPulseHI = !previousPulseHI;
				evenParity = !evenParity;
			}

			++i;
		}
	}
}