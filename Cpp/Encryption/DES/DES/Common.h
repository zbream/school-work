#pragma once

typedef enum { false, true } bool;

// the 64-bit block type
#define ull unsigned long long
#define ush unsigned short

// used for the p-boxes
#define bitset(n, b) (n & (1ULL << (64 - b)))
#define setbit(b) (1ULL << (64 - b))
#define setbits(b1, b2) (setbit(b1) | setbit(b2))