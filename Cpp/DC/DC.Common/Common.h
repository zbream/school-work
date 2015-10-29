#pragma once

// custom data types
#define uint unsigned int
#define uch unsigned char

// char buffer (data stream)
#define CHAR_LIMIT (64)

// frame buffer (3 chars + data stream)
#define FRAME_LIMIT (CHAR_LIMIT + 3)

// raw transmission buffer (0/1 chars)
#define TRANSMIT_LIMIT ((CHAR_LIMIT + 3) * 8)