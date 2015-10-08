#include "Common.h"

/*
Add a parity bit to the specified byte. */
uch p_addParity(uch byte);

/*
Check if the parity of the specified byte is correct. */
bool p_checkParity(uch byte);

/*
Remove the parity bit from the specified byte. */
uch p_stripParity(uch byte);

/*
Convert the specified char to an 8-char array of 0/1 chars.
The array is in little-endian format (LSB to MSB). */
void p_charToArray(uch c, uch arr[8]);

/*
Convert the specified 8-char array of 0/1 chars into an equivalent char.
The array is in little-endian format (LSB to MSB). */
uch p_arrayToChar(uch arr[8]);