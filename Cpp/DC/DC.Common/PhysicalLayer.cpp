#include "PhysicalLayer.h"

#define USE_EVEN_PARITY false

uch p_addParity(uch byte)
{
	uch out = byte;

	// calculate parity
	bool parity = USE_EVEN_PARITY;
	for (int i = 0; i < 8; i++)
	{
		if (byte & 0x1)
		{
			parity = !parity;
		}
		byte >>= 1;
	}
	if (!parity) out |= 0x80;

	return out;
}

bool p_checkParity(uch byte)
{
	// calculate parity
	bool parity = USE_EVEN_PARITY;
	for (int i = 0; i < 8; i++)
	{
		if (byte & 0x1)
		{
			parity = !parity;
		}
		byte >>= 1;
	}

	return parity;
}

uch p_stripParity(uch byte)
{
	return (byte & 0x7f);
}

void p_charToArray(uch c, uch arr[8])
{
	// LSB to MSB
	for (int i = 0; i < 8; i++)
	{
		arr[i] = (c & 0x1) ? '1' : '0';
		c >>= 1;
	}
}

uch p_arrayToChar(uch arr[8])
{
	uch c = 0;

	for (int i = 7; i >= 0; i--)
	{
		c <<= 1;
		c |= (arr[i] == '1') ? 1 : 0;
	}

	return c;
}