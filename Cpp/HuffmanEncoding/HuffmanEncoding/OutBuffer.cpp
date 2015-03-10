/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include "OutBuffer.h"

using namespace std;

OutBuffer::OutBuffer(ofstream& oStream) : outStream(oStream)
{
}

void OutBuffer::Write(const string& encodingString)
{
	// pull each bit from the given encoding string
	for (int i = 0; i < encodingString.length(); i++)
	{
		bits[++bitPos] = (encodingString.at(i) != '0');

		// check if we have 8 bits
		if (GetRemainingBits() == 0)
		{
			// the buffer is full, flush to output stream
			Flush();
		}
	}
}

void OutBuffer::Flush()
{
	unsigned char output = 0;

	// build the output char
	for (int i = 0; i <= bitPos; i++)
	{
		// bit-shift by one, add the new LSB
		output <<= 1;
		output |= bits[i];
	}

	// write the byte to the output stream
	outStream.put(output);
	++bytesOut;

	// reset bits
	bitPos = -1;
}

int OutBuffer::GetRemainingBits()
{
	return NUM_BITS - bitPos - 1;
}

int OutBuffer::GetBytesOut()
{
	return bytesOut;
}