#include "DESRoundEngine.h"

// used for s-boxes
#define uch unsigned char

// function declarations
ull r_pExpansion(ull);
uch r_sBox(uch, uch);
ull r_pStraight(ull);

ull r_runRounds(ull in, ull keys[16])
{
	// initial split
	ull l = (in & 0xffffffff00000000ULL);
	ull r = (in & 0x00000000ffffffffULL) << 32;

	for (ush round = 1; round <= 16; round++)
	{
		ull rOld = r;

		// expansion of right half
		r = r_pExpansion(r);

		// mix in key
		r ^= keys[round - 1];

		// split into s-box blocks
		uch b1 = (r & 0xfc00000000000000ULL) >> (42 + 16);
		uch b2 = (r & 0x03f0000000000000ULL) >> (36 + 16);
		uch b3 = (r & 0x000fc00000000000ULL) >> (30 + 16);
		uch b4 = (r & 0x00003f0000000000ULL) >> (24 + 16);
		uch b5 = (r & 0x000000fc00000000ULL) >> (18 + 16);
		uch b6 = (r & 0x00000003f0000000ULL) >> (12 + 16);
		uch b7 = (r & 0x000000000fc00000ULL) >> (6 + 16);
		uch b8 = (r & 0x00000000003f0000ULL) >> (0 + 16);
		r = 0;
		r = (r | r_sBox(b1, 0)) << 4;
		r = (r | r_sBox(b2, 1)) << 4;
		r = (r | r_sBox(b3, 2)) << 4;
		r = (r | r_sBox(b4, 3)) << 4;
		r = (r | r_sBox(b5, 4)) << 4;
		r = (r | r_sBox(b6, 5)) << 4;
		r = (r | r_sBox(b7, 6)) << 4;
		r = (r | r_sBox(b8, 7));
		r <<= 32;

		// post s-box straight p-box
		r = r_pStraight(r);

		// xor with left half
		r ^= l;

		// old R becomes new L
		l = rOld;
	}

	// final split
	ull out = (r | (l >> 32));
	return out;
}

// Performs the DES Round's initial 32to48-bit expansion p-box.
// Returns the result of this expansion.
ull r_pExpansion(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbits(2, 48);
	if (bitset(in, 2)) out |= setbit(3);
	if (bitset(in, 3)) out |= setbit(4);
	if (bitset(in, 4)) out |= setbits(5, 7);
	if (bitset(in, 5)) out |= setbits(6, 8);
	if (bitset(in, 6)) out |= setbit(9);
	if (bitset(in, 7)) out |= setbit(10);
	if (bitset(in, 8)) out |= setbits(11, 13);
	if (bitset(in, 9)) out |= setbits(12, 14);
	if (bitset(in, 10)) out |= setbit(15);
	if (bitset(in, 11)) out |= setbit(16);
	if (bitset(in, 12)) out |= setbits(17, 19);
	if (bitset(in, 13)) out |= setbits(18, 20);
	if (bitset(in, 14)) out |= setbit(21);
	if (bitset(in, 15)) out |= setbit(22);
	if (bitset(in, 16)) out |= setbits(23, 25);
	if (bitset(in, 17)) out |= setbits(24, 26);
	if (bitset(in, 18)) out |= setbit(27);
	if (bitset(in, 19)) out |= setbit(28);
	if (bitset(in, 20)) out |= setbits(29, 31);
	if (bitset(in, 21)) out |= setbits(30, 32);
	if (bitset(in, 22)) out |= setbit(33);
	if (bitset(in, 23)) out |= setbit(34);
	if (bitset(in, 24)) out |= setbits(35, 37);
	if (bitset(in, 25)) out |= setbits(36, 38);
	if (bitset(in, 26)) out |= setbit(39);
	if (bitset(in, 27)) out |= setbit(40);
	if (bitset(in, 28)) out |= setbits(41, 43);
	if (bitset(in, 29)) out |= setbits(42, 44);
	if (bitset(in, 30)) out |= setbit(45);
	if (bitset(in, 31)) out |= setbit(46);
	if (bitset(in, 32)) out |= setbits(47, 1);

	return out;
}

uch r_sBoxes[8][64] = {
	// S1
	{ 
		14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	},
	// S2
	{
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
	},
	// S3
	{
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
	},
	// S4
	{
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
	},
	// S5
	{
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
	},
	// S6
	{
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, /*10*/6, 0, 8, 13
	},
	// S7
	{
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
	},
	// S8
	{
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, /*10*/0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
	}
};

// Performs the DES Round's 6x4-bit s-box, where box specifies 1-8.
// Returns the 4-bit result.
uch r_sBox(uch in, uch box)
{
	// move bits to proper positions
	uch b2345 = (in >> 1) & 0xF;
	uch b16 = (in & 0x20) | ((in & 0x1) << 4);

	uch b = b16 | b2345;

	uch out = r_sBoxes[box][b];
	return out;
}

// Performs the DES Round's final 32-bit straight p-box.
// Returns this result of this permutation.
ull r_pStraight(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(9);
	if (bitset(in, 2)) out |= setbit(17);
	if (bitset(in, 3)) out |= setbit(23);
	if (bitset(in, 4)) out |= setbit(31);
	if (bitset(in, 5)) out |= setbit(13);
	if (bitset(in, 6)) out |= setbit(28);
	if (bitset(in, 7)) out |= setbit(2);
	if (bitset(in, 8)) out |= setbit(18);
	if (bitset(in, 9)) out |= setbit(24);
	if (bitset(in, 10)) out |= setbit(16);
	if (bitset(in, 11)) out |= setbit(30);
	if (bitset(in, 12)) out |= setbit(6);
	if (bitset(in, 13)) out |= setbit(26);
	if (bitset(in, 14)) out |= setbit(20);
	if (bitset(in, 15)) out |= setbit(10);
	if (bitset(in, 16)) out |= setbit(1);
	if (bitset(in, 17)) out |= setbit(8);
	if (bitset(in, 18)) out |= setbit(14);
	if (bitset(in, 19)) out |= setbit(25);
	if (bitset(in, 20)) out |= setbit(3);
	if (bitset(in, 21)) out |= setbit(4);
	if (bitset(in, 22)) out |= setbit(29);
	if (bitset(in, 23)) out |= setbit(11);
	if (bitset(in, 24)) out |= setbit(19);
	if (bitset(in, 25)) out |= setbit(32);
	if (bitset(in, 26)) out |= setbit(12);
	if (bitset(in, 27)) out |= setbit(22);
	if (bitset(in, 28)) out |= setbit(7);
	if (bitset(in, 29)) out |= setbit(5);
	if (bitset(in, 30)) out |= setbit(27);
	if (bitset(in, 31)) out |= setbit(15);
	if (bitset(in, 32)) out |= setbit(21);

	return out;
}