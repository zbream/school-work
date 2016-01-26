#include "DESMain.h"
#include "DESKeyGen.h"
#include "DESRoundEngine.h"
#include "RNG.h"

// function declarations
ull readBlock(FILE*, ush);
void writeBlock(FILE*, ull, ush);
ull DESBlock(ull[16], ull);
ull pInitial(ull);
ull pFinal(ull);

void DESFileEncrypt(ull key, FILE* in, FILE* out)
{
	rng_seed();

	// generate keys
	ull keys[16];
	kg_generate(key, keys, false);

	// get file length, in bytes
	fseek(in, 0, SEEK_END);
	long inSize = ftell(in);
	fseek(in, 0, SEEK_SET);

	// write file length block
	{
		ull block = inSize;
		block = rng_padBlockWithGarbageL(block, 4);
		block = DESBlock(keys, block);

		writeBlock(out, block, 8);
	}

	// write complete blocks
	long numCompleteBlocks = inSize / 8;
	for (int i = 0; i < numCompleteBlocks; i++)
	{
		// read block and encrypt
		ull block = readBlock(in, 8);
		block = DESBlock(keys, block);

		writeBlock(out, block, 8);
	}

	// write incomplete block
	long numBytesRemaining = inSize % 8;
	if (numBytesRemaining > 0)
	{
		// read remaining, align left, pad with garbage, encrypt
		ull block = readBlock(in, numBytesRemaining);
		block <<= (8 * (8 - numBytesRemaining));
		block = rng_padBlockWithGarbageR(block, 8 - numBytesRemaining);
		block = DESBlock(keys, block);

		writeBlock(out, block, 8);
	}
}

void DESFileDecrypt(ull key, FILE* in, FILE* out)
{
	// generate keys
	ull keys[16];
	kg_generate(key, keys, true);

	// read file length, in bytes
	ull fileLengthBlock = readBlock(in, 8);
	fileLengthBlock = DESBlock(keys, fileLengthBlock);
	long inSize = fileLengthBlock & 0x7FFFFFFF;

	// read complete blocks
	long numCompleteBlocks = inSize / 8;
	for (int i = 0; i < numCompleteBlocks; i++)
	{
		// read block and decrypt
		ull block = readBlock(in, 8);
		block = DESBlock(keys, block);

		// write to output
		writeBlock(out, block, 8);
	}

	// read incomplete block
	long numBytesRemaining = inSize % 8;
	if (numBytesRemaining > 0)
	{
		// read block, decrypt, shift back to right
		ull block = readBlock(in, 8);
		block = DESBlock(keys, block);
		block >>= (8 * (8 - numBytesRemaining));

		writeBlock(out, block, numBytesRemaining);
	}
}

// Read the next nBytes from the in file, as a block.
// Returns the block with the read bytes in LtoR order, aligned right.
ull readBlock(FILE* in, ush nBytes)
{
	// read those bytes
	ull out = 0;
	for (ush i = 0; i < nBytes; i++)
	{
		out <<= 8;
		out |= fgetc(in);
	}

	return out;
}

// Write nBytes of the block to the out file.
// Writes the right-most bytes of the block, LtoR order.
void writeBlock(FILE* out, ull block, ush nBytes)
{
	// [0][0][0][0][0][1][2][3], nBytes=3
	// We want to write the right-most 3 bytes, LtoR

	// create a "stack" of the bytes we wish to write
	ull reverse = 0;
	for (ush i = 0; i < nBytes; i++)
	{
		reverse <<= 8;
		reverse |= (block & 0xFF);
		block >>= 8;
	}

	// write those bytes
	for (ush i = 0; i < nBytes; i++)
	{
		fputc(reverse & 0xFF, out);
		reverse >>= 8;
	}
}

#pragma region DES
// Perform DES on an 8-byte block, using the specified 16 round-keys in order 0-15.
// Returns the resulting block of the DES algorithm.
ull DESBlock(ull keys[16], ull block)
{
	// initial permutation
	block = pInitial(block);

	// rounds
	block = r_runRounds(block, keys);

	// final permutation
	block = pFinal(block);

	return block;
}

// Performs the initial straight p-box of the DES algorithm on a block.
// Returns the resulting block.
ull pInitial(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(40);
	if (bitset(in, 2)) out |= setbit(8);
	if (bitset(in, 3)) out |= setbit(48);
	if (bitset(in, 4)) out |= setbit(16);
	if (bitset(in, 5)) out |= setbit(56);
	if (bitset(in, 6)) out |= setbit(24);
	if (bitset(in, 7)) out |= setbit(64);
	if (bitset(in, 8)) out |= setbit(32);
	if (bitset(in, 9)) out |= setbit(39);
	if (bitset(in, 10)) out |= setbit(7);
	if (bitset(in, 11)) out |= setbit(47);
	if (bitset(in, 12)) out |= setbit(15);
	if (bitset(in, 13)) out |= setbit(55);
	if (bitset(in, 14)) out |= setbit(23);
	if (bitset(in, 15)) out |= setbit(63);
	if (bitset(in, 16)) out |= setbit(31);
	if (bitset(in, 17)) out |= setbit(38);
	if (bitset(in, 18)) out |= setbit(6);
	if (bitset(in, 19)) out |= setbit(46);
	if (bitset(in, 20)) out |= setbit(14);
	if (bitset(in, 21)) out |= setbit(54);
	if (bitset(in, 22)) out |= setbit(22);
	if (bitset(in, 23)) out |= setbit(62);
	if (bitset(in, 24)) out |= setbit(30);
	if (bitset(in, 25)) out |= setbit(37);
	if (bitset(in, 26)) out |= setbit(5);
	if (bitset(in, 27)) out |= setbit(45);
	if (bitset(in, 28)) out |= setbit(13);
	if (bitset(in, 29)) out |= setbit(53);
	if (bitset(in, 30)) out |= setbit(21);
	if (bitset(in, 31)) out |= setbit(61);
	if (bitset(in, 32)) out |= setbit(29);
	if (bitset(in, 33)) out |= setbit(36);
	if (bitset(in, 34)) out |= setbit(4);
	if (bitset(in, 35)) out |= setbit(44);
	if (bitset(in, 36)) out |= setbit(12);
	if (bitset(in, 37)) out |= setbit(52);
	if (bitset(in, 38)) out |= setbit(20);
	if (bitset(in, 39)) out |= setbit(60);
	if (bitset(in, 40)) out |= setbit(28);
	if (bitset(in, 41)) out |= setbit(35);
	if (bitset(in, 42)) out |= setbit(3);
	if (bitset(in, 43)) out |= setbit(43);
	if (bitset(in, 44)) out |= setbit(11);
	if (bitset(in, 45)) out |= setbit(51);
	if (bitset(in, 46)) out |= setbit(19);
	if (bitset(in, 47)) out |= setbit(59);
	if (bitset(in, 48)) out |= setbit(27);
	if (bitset(in, 49)) out |= setbit(34);
	if (bitset(in, 50)) out |= setbit(2);
	if (bitset(in, 51)) out |= setbit(42);
	if (bitset(in, 52)) out |= setbit(10);
	if (bitset(in, 53)) out |= setbit(50);
	if (bitset(in, 54)) out |= setbit(18);
	if (bitset(in, 55)) out |= setbit(58);
	if (bitset(in, 56)) out |= setbit(26);
	if (bitset(in, 57)) out |= setbit(33);
	if (bitset(in, 58)) out |= setbit(1);
	if (bitset(in, 59)) out |= setbit(41);
	if (bitset(in, 60)) out |= setbit(9);
	if (bitset(in, 61)) out |= setbit(49);
	if (bitset(in, 62)) out |= setbit(17);
	if (bitset(in, 63)) out |= setbit(57);
	if (bitset(in, 64)) out |= setbit(25);

	return out;
}

// Performs the final straight p-box of the DES algorithm on a block.
// Returns the resulting block.
ull pFinal(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(58);
	if (bitset(in, 2)) out |= setbit(50);
	if (bitset(in, 3)) out |= setbit(42);
	if (bitset(in, 4)) out |= setbit(34);
	if (bitset(in, 5)) out |= setbit(26);
	if (bitset(in, 6)) out |= setbit(18);
	if (bitset(in, 7)) out |= setbit(10);
	if (bitset(in, 8)) out |= setbit(2);
	if (bitset(in, 9)) out |= setbit(60);
	if (bitset(in, 10)) out |= setbit(52);
	if (bitset(in, 11)) out |= setbit(44);
	if (bitset(in, 12)) out |= setbit(36);
	if (bitset(in, 13)) out |= setbit(28);
	if (bitset(in, 14)) out |= setbit(20);
	if (bitset(in, 15)) out |= setbit(12);
	if (bitset(in, 16)) out |= setbit(4);
	if (bitset(in, 17)) out |= setbit(62);
	if (bitset(in, 18)) out |= setbit(54);
	if (bitset(in, 19)) out |= setbit(46);
	if (bitset(in, 20)) out |= setbit(38);
	if (bitset(in, 21)) out |= setbit(30);
	if (bitset(in, 22)) out |= setbit(22);
	if (bitset(in, 23)) out |= setbit(14);
	if (bitset(in, 24)) out |= setbit(6);
	if (bitset(in, 25)) out |= setbit(64);
	if (bitset(in, 26)) out |= setbit(56);
	if (bitset(in, 27)) out |= setbit(48);
	if (bitset(in, 28)) out |= setbit(40);
	if (bitset(in, 29)) out |= setbit(32);
	if (bitset(in, 30)) out |= setbit(24);
	if (bitset(in, 31)) out |= setbit(16);
	if (bitset(in, 32)) out |= setbit(8);
	if (bitset(in, 33)) out |= setbit(57);
	if (bitset(in, 34)) out |= setbit(49);
	if (bitset(in, 35)) out |= setbit(41);
	if (bitset(in, 36)) out |= setbit(33);
	if (bitset(in, 37)) out |= setbit(25);
	if (bitset(in, 38)) out |= setbit(17);
	if (bitset(in, 39)) out |= setbit(9);
	if (bitset(in, 40)) out |= setbit(1);
	if (bitset(in, 41)) out |= setbit(59);
	if (bitset(in, 42)) out |= setbit(51);
	if (bitset(in, 43)) out |= setbit(43);
	if (bitset(in, 44)) out |= setbit(35);
	if (bitset(in, 45)) out |= setbit(27);
	if (bitset(in, 46)) out |= setbit(19);
	if (bitset(in, 47)) out |= setbit(11);
	if (bitset(in, 48)) out |= setbit(3);
	if (bitset(in, 49)) out |= setbit(61);
	if (bitset(in, 50)) out |= setbit(53);
	if (bitset(in, 51)) out |= setbit(45);
	if (bitset(in, 52)) out |= setbit(37);
	if (bitset(in, 53)) out |= setbit(29);
	if (bitset(in, 54)) out |= setbit(21);
	if (bitset(in, 55)) out |= setbit(13);
	if (bitset(in, 56)) out |= setbit(5);
	if (bitset(in, 57)) out |= setbit(63);
	if (bitset(in, 58)) out |= setbit(55);
	if (bitset(in, 59)) out |= setbit(47);
	if (bitset(in, 60)) out |= setbit(39);
	if (bitset(in, 61)) out |= setbit(31);
	if (bitset(in, 62)) out |= setbit(23);
	if (bitset(in, 63)) out |= setbit(15);
	if (bitset(in, 64)) out |= setbit(7);

	return out;
}
#pragma endregion