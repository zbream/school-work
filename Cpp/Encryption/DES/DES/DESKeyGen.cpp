#include "DESKeyGen.h"

void kg_generate(ull key64, ull keys48[16], bool reverse)
{
	ull key56 = kg_pCompression64to56(key64);

	for (ush i = 1; i <= 16; i++)
	{
		// 1,2,9,16 rotates 1 bits, else rotates 2 bits
		switch (i)
		{
			case 1:
			case 2:
			case 9:
			case 16:
				key56 = kg_rotate1bits(key56);
				break;
			default:
				key56 = kg_rotate2bits(key56);
				break;
		}

		ush index = reverse ? (16 - i) : (i - 1);

		// generate permuted round key
		keys48[index] = kg_pCompression56to48(key56);
	}
}

ull kg_pCompression64to56(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(8);
	if (bitset(in, 2)) out |= setbit(16);
	if (bitset(in, 3)) out |= setbit(24);
	if (bitset(in, 4)) out |= setbit(56);
	if (bitset(in, 5)) out |= setbit(52);
	if (bitset(in, 6)) out |= setbit(44);
	if (bitset(in, 7)) out |= setbit(36);
	//if (bitset(in, 8)) out |= setbit(0);
	if (bitset(in, 9)) out |= setbit(7);
	if (bitset(in, 10)) out |= setbit(15);
	if (bitset(in, 11)) out |= setbit(23);
	if (bitset(in, 12)) out |= setbit(55);
	if (bitset(in, 13)) out |= setbit(51);
	if (bitset(in, 14)) out |= setbit(43);
	if (bitset(in, 15)) out |= setbit(35);
	//if (bitset(in, 16)) out |= setbit(0);
	if (bitset(in, 17)) out |= setbit(6);
	if (bitset(in, 18)) out |= setbit(14);
	if (bitset(in, 19)) out |= setbit(22);
	if (bitset(in, 20)) out |= setbit(54);
	if (bitset(in, 21)) out |= setbit(50);
	if (bitset(in, 22)) out |= setbit(42);
	if (bitset(in, 23)) out |= setbit(34);
	//if (bitset(in, 24)) out |= setbit(0);
	if (bitset(in, 25)) out |= setbit(5);
	if (bitset(in, 26)) out |= setbit(13);
	if (bitset(in, 27)) out |= setbit(21);
	if (bitset(in, 28)) out |= setbit(53);
	if (bitset(in, 29)) out |= setbit(49);
	if (bitset(in, 30)) out |= setbit(41);
	if (bitset(in, 31)) out |= setbit(33);
	//if (bitset(in, 32)) out |= setbit(0);
	if (bitset(in, 33)) out |= setbit(4);
	if (bitset(in, 34)) out |= setbit(12);
	if (bitset(in, 35)) out |= setbit(20);
	if (bitset(in, 36)) out |= setbit(28);
	if (bitset(in, 37)) out |= setbit(48);
	if (bitset(in, 38)) out |= setbit(40);
	if (bitset(in, 39)) out |= setbit(32);
	//if (bitset(in, 40)) out |= setbit(0);
	if (bitset(in, 41)) out |= setbit(3);
	if (bitset(in, 42)) out |= setbit(11);
	if (bitset(in, 43)) out |= setbit(19);
	if (bitset(in, 44)) out |= setbit(27);
	if (bitset(in, 45)) out |= setbit(47);
	if (bitset(in, 46)) out |= setbit(39);
	if (bitset(in, 47)) out |= setbit(31);
	//if (bitset(in, 48)) out |= setbit(0);
	if (bitset(in, 49)) out |= setbit(2);
	if (bitset(in, 50)) out |= setbit(10);
	if (bitset(in, 51)) out |= setbit(18);
	if (bitset(in, 52)) out |= setbit(26);
	if (bitset(in, 53)) out |= setbit(46);
	if (bitset(in, 54)) out |= setbit(38);
	if (bitset(in, 55)) out |= setbit(30);
	//if (bitset(in, 56)) out |= setbit(0);
	if (bitset(in, 57)) out |= setbit(1);
	if (bitset(in, 58)) out |= setbit(9);
	if (bitset(in, 59)) out |= setbit(17);
	if (bitset(in, 60)) out |= setbit(25);
	if (bitset(in, 61)) out |= setbit(45);
	if (bitset(in, 62)) out |= setbit(37);
	if (bitset(in, 63)) out |= setbit(29);
	//if (bitset(in, 64)) out |= setbit(0);

	return out;
}

// rotate 56-bit key
ull kg_rotate1bits(ull key)
{
	// rotate L
	ull L = (key & 0xFFFFFFF000000000ULL);
	L = (L << 1) | ((L & 0x8000000000000000ULL) >> (28 - 1));

	// rotate R
	ull R = (key & 0x0000000FFFFFFF00ULL);
	R = (R << 1) | ((R & 0x0000000800000000ULL) >> (28 - 1));
	R &= 0x0000000FFFFFFF00ULL;

	return (L | R);
}
ull kg_rotate2bits(ull key)
{
	// rotate L
	ull L = (key & 0xFFFFFFF000000000ULL);
	L = (L << 2) | ((L & 0xc000000000000000ULL) >> (28 - 2));

	// rotate R
	ull R = (key & 0x0000000FFFFFFF00ULL);
	R = (R << 2) | ((R & 0x0000000c00000000ULL) >> (28 - 2));
	R &= 0x0000000FFFFFFF00ULL;

	return (L | R);
}

ull kg_pCompression56to48(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(5);
	if (bitset(in, 2)) out |= setbit(24);
	if (bitset(in, 3)) out |= setbit(7);
	if (bitset(in, 4)) out |= setbit(16);
	if (bitset(in, 5)) out |= setbit(6);
	if (bitset(in, 6)) out |= setbit(10);
	if (bitset(in, 7)) out |= setbit(20);
	if (bitset(in, 8)) out |= setbit(18);
	//if (bitset(in, 9)) out |= setbit(0);
	if (bitset(in, 10)) out |= setbit(12);
	if (bitset(in, 11)) out |= setbit(3);
	if (bitset(in, 12)) out |= setbit(15);
	if (bitset(in, 13)) out |= setbit(23);
	if (bitset(in, 14)) out |= setbit(1);
	if (bitset(in, 15)) out |= setbit(9);
	if (bitset(in, 16)) out |= setbit(19);
	if (bitset(in, 17)) out |= setbit(2);
	//if (bitset(in, 18)) out |= setbit(0);
	if (bitset(in, 19)) out |= setbit(14);
	if (bitset(in, 20)) out |= setbit(22);
	if (bitset(in, 21)) out |= setbit(11);
	//if (bitset(in, 22)) out |= setbit(0);
	if (bitset(in, 23)) out |= setbit(13);
	if (bitset(in, 24)) out |= setbit(4);
	//if (bitset(in, 25)) out |= setbit(0);
	if (bitset(in, 26)) out |= setbit(17);
	if (bitset(in, 27)) out |= setbit(21);
	if (bitset(in, 28)) out |= setbit(8);
	if (bitset(in, 29)) out |= setbit(47);
	if (bitset(in, 30)) out |= setbit(31);
	if (bitset(in, 31)) out |= setbit(27);
	if (bitset(in, 32)) out |= setbit(48);
	if (bitset(in, 33)) out |= setbit(35);
	if (bitset(in, 34)) out |= setbit(41);
	//if (bitset(in, 35)) out |= setbit(0);
	if (bitset(in, 36)) out |= setbit(46);
	if (bitset(in, 37)) out |= setbit(28);
	//if (bitset(in, 38)) out |= setbit(0);
	if (bitset(in, 39)) out |= setbit(39);
	if (bitset(in, 40)) out |= setbit(32);
	if (bitset(in, 41)) out |= setbit(25);
	if (bitset(in, 42)) out |= setbit(44);
	//if (bitset(in, 43)) out |= setbit(0);
	if (bitset(in, 44)) out |= setbit(37);
	if (bitset(in, 45)) out |= setbit(34);
	if (bitset(in, 46)) out |= setbit(43);
	if (bitset(in, 47)) out |= setbit(29);
	if (bitset(in, 48)) out |= setbit(36);
	if (bitset(in, 49)) out |= setbit(38);
	if (bitset(in, 50)) out |= setbit(45);
	if (bitset(in, 51)) out |= setbit(33);
	if (bitset(in, 52)) out |= setbit(26);
	if (bitset(in, 53)) out |= setbit(42);
	//if (bitset(in, 54)) out |= setbit(0);
	if (bitset(in, 55)) out |= setbit(30);
	if (bitset(in, 56)) out |= setbit(40);

	return out;
}