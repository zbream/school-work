#include "AESMain.h"
#include "AESKeyGen.h"
#include "AESTransformations.h"
#include "RNG.h"

// function declarations
void readBlock(FILE* in, uch block[16], uch nBytes);
void writeBlock(FILE* out, uch block[16], uch nBytes);

void AESFileEncrypt(uch key[16], FILE* in, FILE* out)
{
	rng_seed();

	uch block[4][4];

	// generate keys
	uch keys[11][4][4];
	kg_generate(key, keys);
	
	// get file length, in bytes
	fseek(in, 0, SEEK_END);
	long inSize = ftell(in);
	fseek(in, 0, SEEK_SET);

	// write file length block
	{
		// copy size to last word of block
		long x = inSize;
		for (int i = 3; i >= 0; i--)
		{
			block[3][i] = (x & 0xFF);
			x >>= 8;
		}

		// pad with garbage
		rng_padBlockWithGarbageL(block, 12);

		// encrypt and write
		AESBlockEncrypt(keys, block);
		writeBlock(out, block, 16);
	}

	// write complete blocks
	long numCompleteBlocks = inSize / 16;
	for (int i = 0; i < numCompleteBlocks; i++)
	{
		// read block
		readBlock(in, block, 16);
		
		// encrypt and write
		AESBlockEncrypt(keys, block);
		writeBlock(out, block, 16);
	}

	// write incomplete block
	long numBytesRemaining = inSize % 16;
	if (numBytesRemaining > 0)
	{
		// read remaining
		readBlock(in, block, numBytesRemaining);

		// pad with garbage
		rng_padBlockWithGarbageR(block, 16 - numBytesRemaining);

		// encrypt and write
		AESBlockEncrypt(keys, block);
		writeBlock(out, block, 16);
	}
}

void AESFileDecrypt(uch key[16], FILE* in, FILE* out)
{
	uch block[4][4];

	// generate keys
	uch keys[11][4][4];
	kg_generate(key, keys);

	// read file length, in bytes
	long inSize = 0;
	{
		// read and decrypt
		readBlock(in, block, 16);
		AESBlockDecrypt(keys, block);

		// copy size from last word of block
		for (int i = 0; i < 4; i++)
		{
			inSize <<= 8;
			inSize |= block[3][i];
		}
	}

	// read complete blocks
	long numCompleteBlocks = inSize / 16;
	for (int i = 0; i < numCompleteBlocks; i++)
	{
		// read block
		readBlock(in, block, 16);

		// decrypt and write
		AESBlockDecrypt(keys, block);
		writeBlock(out, block, 16);
	}

	// read incomplete block
	long numBytesRemaining = inSize % 16;
	if (numBytesRemaining > 0)
	{
		// read block
		readBlock(in, block, 16);

		// decrypt and write
		AESBlockDecrypt(keys, block);
		writeBlock(out, block, numBytesRemaining);
	}
}

void readBlock(FILE* in, uch block[16], uch nBytes)
{	
	for (int i = 0; i < nBytes; i++)
	{
		block[i] = fgetc(in);
	}
}

void writeBlock(FILE* out, uch block[16], uch nBytes)
{
	for (int i = 0; i < nBytes; i++)
	{
		fputc(block[i], out);
	}
}

void AESBlockEncrypt(uch keys[11][4][4], uch state[4][4])
{
	t_AddRoundKey(state, keys[0]);

	for (int round = 1; round <= 10; round++)
	{
		t_SubBytes(state);
		t_ShiftRows(state);
		if (round < 10) t_MixColumns(state);
		t_AddRoundKey(state, keys[round]);
	}
}

void AESBlockDecrypt(uch keys[11][4][4], uch state[4][4])
{
	t_AddRoundKey(state, keys[10]);

	for (int round = 1; round <= 10; round++)
	{
		t_InvShiftRows(state);
		t_InvSubBytes(state);
		t_AddRoundKey(state, keys[10 - round]);
		if (round < 10) t_InvMixColumns(state);
	}
}