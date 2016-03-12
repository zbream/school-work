#include "Common.h"
#include "Sha256.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	// prompt for file path
	std::cout << "Enter a path:\n";
	std::string inputPath;
	std::cin >> inputPath;

	// store entire input in vector
	std::vector<char> chars;

	// open file
	std::ifstream input(inputPath.c_str(), std::ios_base::in | std::ios_base::binary);
	if (input.fail())
	{
		std::cout << "Unable to open file for reading. Exiting...\n";
		return -1;
	}

	// and read entire input
	char c;
	while (input.get(c))
	{
		chars.push_back(c);
	}
	input.close();

	ull lengthBytes = chars.size();
	ull lengthBits = lengthBytes << 3;

	// pad for SHA-256
	chars.push_back(0x80);
	lengthBytes++;
	int remainder = lengthBytes % 64;
	int kBytes = (remainder <= 56) ? 56 - remainder : 64 + 56 - remainder;
	for (int i = 0; i < kBytes; i++)
	{
		chars.push_back(0x0);
	}

	// append length in bits
	std::vector<char>::iterator insertPos = chars.end();
	for (int i = 0; i < 8; i++)
	{
		chars.insert(insertPos, (char)lengthBits);
		lengthBits >>= 8;
	}

	// begin hash
	uint H[8];
	initializeHash(H);

	// split into chunks and hash
	uint M[64], temp;
	int numChunks = chars.size() / 64;
	for (int i = 0; i < numChunks; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			temp = 0;
			for (int k = 0; k < 4; k++)
			{
				temp <<= 8;
				temp |= (unsigned char)(chars[64 * i + 4 * j + k]);
			}
			M[j] = temp;
		}

		performHashOnChunk(H, M);
	}

	// print the hash
	for (int i = 0; i < 8; i++)
	{
		std::printf("%s%8X", (i ? " " : ""), H[i]);
	}

	return 0;
}
