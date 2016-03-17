#include "Common.h"
#include "Sha256.h"
#include <string.h>
#include <iostream>
#include <fstream>

int main()
{
	// prompt for file path
	std::cout << "Enter a path:\n";
	std::string inputPath;
	std::cin >> inputPath;

	// open file
	std::ifstream input(inputPath.c_str(), std::ios_base::in | std::ios_base::binary);
	if (input.fail())
	{
		std::cout << "Unable to open file for reading. Exiting...\n";
		return -1;
	}

	// begin hash
	uint H[8];
	initializeHash(H);

	char c;

	// buffer for current M
	char charBuffer[64];
	int charI = 0;
	uint M[16];

	// once input is done, we calculate how many zero bytes must be appended
	// using the total bytes read
	ull bytesRead = 0;
	bool isMoreInput = true;
	int zeroBytesToAppend;

	// once we have appended the length, we only write to the last buffer and quit
	bool haveAppendedLength = false;

	while (true)
	{
		if (charI < 64)
		{
			// there is space in the char buffer, add to it

			if (isMoreInput)
			{
				// there is (possibly) more input on the file

				if (input.get(c))
				{
					// got input from the file

					charBuffer[charI++] = c;
					bytesRead++;
				}
				else
				{
					// no more input from the file, append the 1-bit
					isMoreInput = false;

					charBuffer[charI++] = 0x80;

					// calculate the 0-bytes to add
					int remainder = (bytesRead + 1) % 64;
					zeroBytesToAppend = (remainder <= 56) ? 56 - remainder : 64 + 56 - remainder;
				}
			}
			else
			{
				// no more input on the file, append 0-bytes or length

				if (zeroBytesToAppend > 0)
				{
					// there are more 0-bytes to append

					charBuffer[charI++] = 0x0;
					zeroBytesToAppend--;
				}
				else
				{
					// only have the remaining length to add

					ull bitsRead = bytesRead << 3;

					for (int i = 7; i >= 0; i--)
					{
						charBuffer[charI + i] = (unsigned char)bitsRead;
						bitsRead >>= 8;
					}
					charI += 8;

					haveAppendedLength = true;
				}
			}
		}
		else
		{
			// no more space in the char buffer, parse and perform the hash
			uint temp;
			for (int i = 0; i < 16; i++)
			{
				temp = 0;
				for (int j = 0; j < 4; j++)
				{
					temp <<= 8;
					temp |= (unsigned char)(charBuffer[4 * i + j]);
				}
				M[i] = temp;
			}

			performHashOnChunk(H, M);

			// reset char buffer
			charI = 0;

			// if we have appended the length, this WAS the final char buffer
			if (haveAppendedLength)
			{
				break;
			}
		}
	}

	input.close();

	// print the hash
	for (int i = 0; i < 8; i++)
	{
		std::printf("%s%08X", (i ? " " : ""), H[i]);
	}
	std::cout << std::endl;

	return 0;
}
