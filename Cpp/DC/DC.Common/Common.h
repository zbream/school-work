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

// case insensitive check for equality
#define streq(s1, s2) !_stricmp(s1, s2)

// enum declarations
typedef enum { EC_NONE, EC_CRC, EC_HAMMING } EC;


// OLD BELOW

// frame buffer (3 chars + data stream)
//#define FRAME_LIMIT (CHAR_LIMIT + 3)

// raw transmission buffer (0/1 chars)
//#define TRANSMIT_LIMIT ((CHAR_LIMIT + 3) * 8)
//#define TRANSMIT_LIMIT ((CHAR_LIMIT + 3) * 12)