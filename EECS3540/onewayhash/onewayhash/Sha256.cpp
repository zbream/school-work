/* Ream, Zack - One Way Hash (SHA-256)
EECS 3540 - 3/17/2016 */

#include "Sha256.h"
//#include <stdio.h>
#include <cstring>

// === function declarations
uint ch(uint, uint, uint);
uint maj(uint, uint, uint);
uint bigSigma0(uint);
uint bigSigma1(uint);
uint smallSigma0(uint);
uint smallSigma1(uint);

// === algorithm constants
const uint hnm1[8] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
const uint k[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

// === program

void initializeHash(uint H[8])
{
	std::memcpy(H, hnm1, 32);
}

void performHashOnChunk(uint H[8], const uint M[16])
{
	// initialize message schedule
	uint W[64];
	std::memcpy(W, M, 64);
	for (int t = 16; t <= 63; t++)
	{
		W[t] = smallSigma1(W[t - 2]) + W[t - 7] + smallSigma0(W[t - 15]) + W[t - 16];
	}

	// initialize working variables
	uint a = H[0];
	uint b = H[1];
	uint c = H[2];
	uint d = H[3];
	uint e = H[4];
	uint f = H[5];
	uint g = H[6];
	uint h = H[7];
	uint T1, T2;

	// main compression
	for (int t = 0; t <= 63; t++)
	{
		T1 = h + bigSigma1(e) + ch(e, f, g) + k[t] + W[t];
		T2 = bigSigma0(a) + maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		//printf("t=%2i: %08X %08X %08X %08X %08X %08X %08X %08X \n", t, a, b, c, d, e, f, g, h);
	}

	// intermediate hash value
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
	H[5] += f;
	H[6] += g;
	H[7] += h;
}

uint rotr(uint x, short n)
{
	short N = (sizeof(uint) << 3) - n;

	return (x << N) | (x >> n);
}

uint ch(uint x, uint y, uint z)
{
	return ((x & y) ^ (~x & z));
}

uint maj(uint x, uint y, uint z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint bigSigma0(uint x)
{
	return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22));
}

uint bigSigma1(uint x)
{
	return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25));
}

uint smallSigma0(uint x)
{
	return (rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3));
}

uint smallSigma1(uint x)
{
	return (rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10));
}
