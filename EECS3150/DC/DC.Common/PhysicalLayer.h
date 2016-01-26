#include "Common.h"

/*
Add an ASCII parity bit to the specified byte. */
uch p_addParity(uch byte);

/*
Check if the ASCII parity of the specified byte is correct. */
bool p_checkParity(uch byte);

/*
Remove the ASCII parity bit from the specified byte. */
uch p_stripParity(uch byte);

/*
Convert the specified char to an 8-char array of 0/1 chars.
The array is in little-endian format (LSB to MSB). */
void p_charToArray(uch c, uch arr[8]);

/*
Convert the specified 8-char array of 0/1 chars into an equivalent char.
The array is in little-endian format (LSB to MSB). */
uch p_arrayToChar(uch arr[8]);

/*
Calculates the CRC-ANSI remainder from the first dataN bytes of dataBuffer.
Returns the 2-byte remainder. */
uint p_crcAnsi(uch dataBuffer[DATA_LIMIT], uint dataN);

/*
Convert the specified char to a 12-bit hamming code.
Hamming code is a 12-char array of 0/1 chars. */
void p_hammingCharTo12(uch byte, uch hammingBuffer[12]);

/*
Convert the specified 12-bit hamming code to a char.
Hamming code is a 12-char array of 0/1 chars. */
uch p_hamming12ToChar(uch hammingBuffer[12]);

/*
Get the syndrome of the specified 12-bit hamming code.
Hamming code is a 12-char array of 0/1 chars. */
uint p_hammingGetSyndrome(uch hammingBuffer[12]);