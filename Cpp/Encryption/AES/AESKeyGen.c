#include "AESKeyGen.h"
#include "AESTransformations.h"

// Round Constants
uch kg_rConstant[] = {
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d
};

void kg_generate(uch userKey[16], uch keys[11][4][4])
{
	// prepare round 0
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			keys[0][c][r] = userKey[4 * c + r];
		}
	}

	// temporary word for each round
	uch t[4];
	
	for (uch round = 1; round <= 10; round++)
	{
		// load t from previous round, left-rotated one byte
		t[0] = keys[round - 1][3][1];
		t[1] = keys[round - 1][3][2];
		t[2] = keys[round - 1][3][3];
		t[3] = keys[round - 1][3][0];

		// run bytes through substitution
		t[0] = t_SubBytesSubstitution(t[0]);
		t[1] = t_SubBytesSubstitution(t[1]);
		t[2] = t_SubBytesSubstitution(t[2]);
		t[3] = t_SubBytesSubstitution(t[3]);
		
		// xor with constant
		uch c = kg_rConstant[round];
		t[0] ^= c;

		// get rest of round key
		// w4 = t ^ w0
		keys[round][0][0] = t[0] ^ keys[round - 1][0][0];
		keys[round][0][1] = t[1] ^ keys[round - 1][0][1];
		keys[round][0][2] = t[2] ^ keys[round - 1][0][2];
		keys[round][0][3] = t[3] ^ keys[round - 1][0][3];
		// w5 = w4 ^ w1
		keys[round][1][0] = keys[round][0][0] ^ keys[round - 1][1][0];
		keys[round][1][1] = keys[round][0][1] ^ keys[round - 1][1][1];
		keys[round][1][2] = keys[round][0][2] ^ keys[round - 1][1][2];
		keys[round][1][3] = keys[round][0][3] ^ keys[round - 1][1][3];
		// w6 = w5 ^ w2
		keys[round][2][0] = keys[round][1][0] ^ keys[round - 1][2][0];
		keys[round][2][1] = keys[round][1][1] ^ keys[round - 1][2][1];
		keys[round][2][2] = keys[round][1][2] ^ keys[round - 1][2][2];
		keys[round][2][3] = keys[round][1][3] ^ keys[round - 1][2][3];
		// w7 = w6 ^ w3
		keys[round][3][0] = keys[round][2][0] ^ keys[round - 1][3][0];
		keys[round][3][1] = keys[round][2][1] ^ keys[round - 1][3][1];
		keys[round][3][2] = keys[round][2][2] ^ keys[round - 1][3][2];
		keys[round][3][3] = keys[round][2][3] ^ keys[round - 1][3][3];
	}
}