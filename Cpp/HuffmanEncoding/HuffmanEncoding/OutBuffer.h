/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include <fstream>

/*
Maintains and writes a buffer of character strings as char's to an output stream.
A character string is made up of 1's and 0's.
*/
class OutBuffer
{
public:
	OutBuffer(std::ofstream&);

	/*
	Write the character string to the buffer.
	If the buffer gets full while adding, flush the buffer to the output stream.
	*/
	void Write(const std::string&);

	/*
	Returns how many remaining bits are necessary to fill and flush the buffer.
	*/
	int GetRemainingBits();

	/*
	Returns how many full bytes have been written to the output stream.
	*/
	int GetBytesOut();

private:
	// Number of bits in a byte
	static const int NUM_BITS = 8;

	std::ofstream& outStream;
	bool bits[NUM_BITS];
	int bitPos = -1;

	/*
	Write the current buffer to the output stream as a char, and resets the buffer.
	*/
	void Flush();

	// full bytes written to the output stream
	int bytesOut = 0;
};

