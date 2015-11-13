#include "Common.h"

/*
Add the ASCII parity bit of the first charN bytes of charBuffer. */
void l_addCharParity(uch charBuffer[CHAR_LIMIT], uint charN);

/*
Validate the ASCII parity of the first charN bytes of charBuffer. 
Returns true if all valid, false otherwise. */
bool l_validateCharParity(uch charBuffer[CHAR_LIMIT], uint charN);

/*
Remove the ASCII parity bit of the first charN bytes of charBuffer. */
void l_stripCharParity(uch charBuffer[CHAR_LIMIT], uint charN);

/*
Prepare dataBuffer, for no error detection or correction.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareData(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Parse charBuffer, for no error detection or correction.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseData(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

/*
Prepare dataBuffer, for CRC-ANSI error detection.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareDataCrc(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Validate the CRC-ANSI of the first dataN bytes of dataBuffer (including the CRC checksum).
Returns true if valid, false otherwise. */
bool l_validateDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN);

/*
Parse charBuffer, for CRC-ANSI error detection. The CRC is assumed to be valid.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

/*
Prepare dataBuffer, for Hamming 8-4 error correction.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareDataHamming(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Parse charBuffer, for Hamming 8-4 error correction.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseDataHamming(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

int l_introduceErrors(uch dataBuffer[DATA_LIMIT], uint dataN, int maxErrors, int errorPos[]);