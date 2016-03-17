/* Ream, Zack - One Way Hash (SHA-256)
EECS 3540 - 3/17/2016 */

#include "Common.h"
#include "Sha256.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

// === constants
// setting to 1 simulates a single-threaded implementation
#define BUFFER_LENGTH (5)

// === function declarations
void* inputThreadWork(void*);
void* hashThreadWork(void*);

// === globals
std::ifstream input;
bool inputDone = false;

uint buffer[BUFFER_LENGTH][16];
int bufferStart;
int bufferLength;

uint H[8];

// === program
int main()
{
	// prompt for file path
	std::cout << "Enter a path:\n";
	std::string inputPath;
	std::cin >> inputPath;

	// open file
	input.open(inputPath.c_str(), std::ios_base::in | std::ios_base::binary);
	if (input.fail())
	{
		std::cout << "Unable to open file for reading. Exiting..." << std::endl;
		return -1;
	}

	// prepare hash
	initializeHash(H);

	// create threads
	pthread_t inputThread, hashThread;
	pthread_create(&inputThread, NULL, inputThreadWork, NULL);
	pthread_create(&hashThread, NULL, hashThreadWork, NULL);

	// and wait for completion
	pthread_join(inputThread, NULL);
	pthread_join(hashThread, NULL);

	input.close();

	// print the hash
	for (int i = 0; i < 8; i++)
	{
		std::printf("%s%08X", (i ? " " : ""), H[i]);
	}
	std::cout << std::endl;

	return 0;
}

void* inputThreadWork(void* data)
{
	char c;

	// buffer for current M
	char charBuffer[64];
	int charI = 0;

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
			// no more space in the char buffer, wait to add to global buffer

			if (bufferLength < BUFFER_LENGTH)
			{
				// there is room for another buffer

				int bufferDestI = (bufferStart + bufferLength) % BUFFER_LENGTH;

				// format into uints and add to global buffer
				uint temp;
				for (int i = 0; i < 16; i++)
				{
					temp = 0;
					for (int j = 0; j < 4; j++)
					{
						temp <<= 8;
						temp |= (unsigned char)(charBuffer[4 * i + j]);
					}
					buffer[bufferDestI][i] = temp;
				}
				bufferLength++;

				// reset char buffer
				charI = 0;

				// if we have appended length, this WAS the final char buffer
				if (haveAppendedLength)
				{
					break;
				}
			}
		}
	}

	inputDone = true;

	pthread_exit(NULL);
	return NULL;
}

void* hashThreadWork(void* data)
{
	while (!inputDone || bufferLength > 0)
	{
		if (bufferLength > 0)
		{
			// we have a buffered chunk to hash
			performHashOnChunk(H, buffer[bufferStart]);

			bufferStart = (bufferStart + 1) % BUFFER_LENGTH;
			bufferLength--;
		}
	}

	pthread_exit(NULL);
	return NULL;
}
