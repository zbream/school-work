/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include <fstream>

/*
Reads from an input stream, bit-by-bit.

Reads a char into the bit buffer, returns these bits one by one.
Pulls another char into the buffer of bits as needed.
*/
class InBuffer
{
public:
	InBuffer(std::ifstream&);
	
	/*
	Reads the next bit from the input stream. Returns -1 if eof.
	If the bit buffer is empty, loads the next char into the buffer.
	*/
	int Read();
	
	/*
	Returns how many full bytes have been read from the input stream.
	*/
	int GetBytesIn();

private:
	// Number of bits in a byte
	static const int NUM_BITS = 8;

	std::ifstream& inStream;
	bool bits[NUM_BITS];
	int bitPos = 0;

	/*
	Load the next char into the bit buffer and resets the buffer.
	Return true if a char was read, false if eof.
	*/
	bool LoadNext();

	// full bytes read from the input stream
	int bytesIn = 0;
};

