#pragma once

// custom data types
#define uint unsigned int
#define uch unsigned char

// char buffer size (data stream)
#define CHAR_LIMIT (64)

// data [0's and 1's] buffer size (big enough to fit hamming bits)
#define DATA_LIMIT (CHAR_LIMIT * 12)

// transmit buffer size (dataBuffer + 3 frame chars)
#define TRANSMIT_LIMIT (DATA_LIMIT + 3)

// the size of a full transmission for the various EC modes
#define MAX_TRANSMIT_NONE (CHAR_LIMIT * 8 + 3)
#define MAX_TRANSMIT_CRC (CHAR_LIMIT * 8 + 16 + 3)
#define MAX_TRANSMIT_HAMMING (TRANSMIT_LIMIT)

// case insensitive check for equality
#define streq(s1, s2) !_stricmp(s1, s2)

// enum declarations
enum FLAG_ER { FLAG_ER_PARITY = 1, FLAG_ER_HAMMING_DETECTED = 2, FLAG_ER_HAMMING_CORRECTED = 4 };