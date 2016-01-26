#include "AESMain.h"
#include "AESKeyGen.h"
#include "AESTransformations.h"
#include "RNG.h"

// function declarations
void readBlock(FILE*, uch, uch[16]);
void writeBlock(FILE*, uch, uch[16]);
void AESBlockEncrypt(uch[11][4][4], uch[4][4]);
void AESBlockDecrypt(uch[11][4][4], uch[4][4]);

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
		writeBlock(out, 16, block);
	}

	// write complete blocks
	long numCompleteBlocks = inSize / 16;
	for (int i = 0; i < numCompleteBlocks; i++)
	{
		// read block
		readBlock(in, 16, block);
		
		// encrypt and write
		AESBlockEncrypt(keys, block);
		writeBlock(out, 16, block);
	}

	// write incomplete block
	long numBytesRemaining = inSize % 16;
	if (numBytesRemaining > 0)
	{
		// read remaining
		readBlock(in, numBytesRemaining, block);

		// pad with garbage
		rng_padBlockWithGarbageR(block, 16 - numBytesRemaining);

		// encrypt and write
		AESBlockEncrypt(keys, block);
		writeBlock(out, 16, block);
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
		readBlock(in, 16, block);
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
		readBlock(in, 16, block);

		// decrypt and write
		AESBlockDecrypt(keys, block);
		writeBlock(out, 16, block);
	}

	// read incomplete block
	long numBytesRemaining = inSize % 16;
	if (numBytesRemaining > 0)
	{
		// read block
		readBlock(in, 16, block);

		// decrypt and write
		AESBlockDecrypt(keys, block);
		writeBlock(out, numBytesRemaining, block);
	}
}

// Read the next nBytes from the in file, into the given block.
// Does not modify the last (16-nBytes) bytes of the given block.
void readBlock(FILE* in, uch nBytes, uch block[16])
{	
	for (int i = 0; i < nBytes; i++)
	{
		block[i] = fgetc(in);
	}
}

// Write the first nBytes of the given block to the out file.
void writeBlock(FILE* out, uch nBytes, uch block[16])
{
	for (int i = 0; i < nBytes; i++)
	{
		fputc(block[i], out);
	}
}

// Perform AES Encryption on the specified 16-byte block, using the specified round-keys.
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

// Perform AES Decryption on the specified 16-byte block, using the specified round-keys.
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