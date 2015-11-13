#include "PhysicalLayer.h"
#include <cstring>

#define USE_EVEN_PARITY false

#define toChar(bit) ((bit) ? '1' : '0')
#define toBit(character) (character - '0')

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
		arr[i] = toChar(c & 0x1);
		c >>= 1;
	}
}

uch p_arrayToChar(uch arr[8])
{
	uch c = 0;

	for (int i = 7; i >= 0; i--)
	{
		c <<= 1;
		c |= toBit(arr[i]);
	}

	return c;
}

const uint ANSI = 0x8005;

uint p_crcAnsi(uch dataBuffer[DATA_LIMIT], uch dataN)
{
	uint reg = 0;

	for (int i = 0; i < dataN; i++)
	{
		// check MSB
		bool doXOR = ((reg & 0x8000) != 0);

		// add next message bit
		reg <<= 1;
		reg |= toBit(dataBuffer[i]);

		if (doXOR)
		{
			reg ^= ANSI;
		}
	}

	return (reg & 0xffff);
}

uch hammingCheckBits[5];

void p_hammingCharTo12(uch byte, uch hammingBuffer[12])
{
	// data bits go LSB to MSB
	hammingBuffer[11] = toChar(byte & 0x80);
	hammingBuffer[10] = toChar(byte & 0x40);
	hammingBuffer[9] = toChar(byte & 0x20);
	hammingBuffer[8] = toChar(byte & 0x10);
	hammingBuffer[6] = toChar(byte & 0x8);
	hammingBuffer[5] = toChar(byte & 0x4);
	hammingBuffer[4] = toChar(byte & 0x2);
	hammingBuffer[2] = toChar(byte & 0x1);

	// p1(0) = 1,3,5,7,9,11(0,2,4,6,8,10)
	uint p1 = (hammingBuffer[2] + hammingBuffer[4] + hammingBuffer[6] + hammingBuffer[8] + hammingBuffer[10]);
	hammingBuffer[0] = toChar(p1 % 2);

	// p2(1) = 2,3,6,7,10,11(1,2,5,6,9,10)
	uint p2 = (hammingBuffer[2] + hammingBuffer[5] + hammingBuffer[6] + hammingBuffer[9] + hammingBuffer[10]);
	hammingBuffer[1] = toChar(p2 % 2);

	// p4(3) = 4,5,6,7,12(3,4,5,6,11)
	uint p4 = (hammingBuffer[4] + hammingBuffer[5] + hammingBuffer[6] + hammingBuffer[11]);
	hammingBuffer[3] = toChar(p4 % 2);

	// p8(7) = 8,9,10,11,12(7,8,9,10,11)
	uint p8 = (hammingBuffer[8] + hammingBuffer[9] + hammingBuffer[10] + hammingBuffer[11]);
	hammingBuffer[7] = toChar(p8 % 2);
}

uch p_hamming12ToChar(uch hammingBuffer[12])
{
	uch byte = 0;
	
	// data bits go LSB to MSB
	byte |= toBit(hammingBuffer[11]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[10]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[9]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[8]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[6]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[5]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[4]);
	byte <<= 1;
	byte |= toBit(hammingBuffer[2]);

	return byte;
}

uint p_hammingGetSyndrome(uch hammingBuffer[12])
{
	uint syndrome = 0;

	// p1(0) = 1,3,5,7,9,11(0,2,4,6,8,10)
	uint p1 = (hammingBuffer[0] + hammingBuffer[2] + hammingBuffer[4] + hammingBuffer[6] + hammingBuffer[8] + hammingBuffer[10]);
	if (p1 % 2) syndrome += 1;

	// p2(1) = 2,3,6,7,10,11(1,2,5,6,9,10)
	uint p2 = (hammingBuffer[1] + hammingBuffer[2] + hammingBuffer[5] + hammingBuffer[6] + hammingBuffer[9] + hammingBuffer[10]);
	if (p2 % 2) syndrome += 2;

	// p4(3) = 4,5,6,7,12(3,4,5,6,11)
	uint p4 = (hammingBuffer[3] + hammingBuffer[4] + hammingBuffer[5] + hammingBuffer[6] + hammingBuffer[11]);
	if (p4 % 2) syndrome += 4;

	// p8(7) = 8,9,10,11,12(7,8,9,10,11)
	uint p8 = (hammingBuffer[7] + hammingBuffer[8] + hammingBuffer[9] + hammingBuffer[10] + hammingBuffer[11]);
	if (p8 % 2) syndrome += 8;

	return syndrome;
}