#pragma once

// the 64-bit block type
#define ull unsigned long long
#define ush unsigned short

// used for the p-boxes
#define bitset(n, b) (n & (1ULL << (64 - b)))
#define setbit(n, b) (1ULL << (64 - b))
#define setbits(n, b1, b2) ((1ULL << (64 - b1)) | (1ULL << (64 - b2)));