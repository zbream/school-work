#pragma once

typedef enum { false, true } bool;

// The 64-bit block type. For the DES algorithm, MSB is always bit1.
#define ull unsigned long long

// Smaller data type used when specifying small numbers, like bit-shifts.
#define ush unsigned short

// Used for the p-boxes.
#define bitset(n, b) (n & (1ULL << (64 - b)))
#define setbit(b) (1ULL << (64 - b))
#define setbits(b1, b2) (setbit(b1) | setbit(b2))