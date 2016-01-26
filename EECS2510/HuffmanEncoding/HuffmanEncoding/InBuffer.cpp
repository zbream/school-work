/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include "InBuffer.h"

using namespace std;

InBuffer::InBuffer(ifstream& iStream) : inStream(iStream)
{
}

int InBuffer::Read()
{
	// check if buffer is empty
	if (bitPos <= 0)
	{
		// load next byte, since buffer is empty
		if (!LoadNext())
		{
			// report eof
			return -1;
		}
	}

	// return the next bit
	return bits[--bitPos];
}

bool InBuffer::LoadNext()
{
	unsigned char input = inStream.get();

	if (inStream.eof())
	{
		// file is empty
		return false;
	}

	// since not eof, we loaded another byte
	++bytesIn;

	// build the buffer from the input char
	for (int i = 0; i < NUM_BITS; i++)
	{
		// determine bit at LSB, then bit-shift by one
		bits[i] = input & 1;
		input >>= 1;
	}

	// reset bits
	bitPos = NUM_BITS;

	// read a bit
	return true;
}

int InBuffer::GetBytesIn()
{
	return bytesIn;
}