#pragma once

// custom data types
#define uint unsigned int
#define uch unsigned char

// char buffer (data stream)
#define CHAR_LIMIT (64)

// data [0/1] buffer (big enough to fit hamming bits)
#define DATA_LIMIT (CHAR_LIMIT * 12)

// transmit limit (dataBuffer + 3 frame chars)
#define TRANSMIT_LIMIT (DATA_LIMIT + 3)

#define MAX_TRANSMIT_NONE (CHAR_LIMIT * 8 + 3)
#define MAX_TRANSMIT_CRC (CHAR_LIMIT * 8 + 16 + 3)
#define MAX_TRANSMIT_HAMMING (TRANSMIT_LIMIT)

// case insensitive check for equality
#define streq(s1, s2) !_stricmp(s1, s2)

// enum declarations
enum EC { EC_NONE, EC_CRC, EC_HAMMING };
char* ECString(EC);