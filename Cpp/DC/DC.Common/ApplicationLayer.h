#include "Common.h"
#include <stdio.h>
#include <string>

// enum of error correction mode
enum EC { EC_NONE, EC_CRC, EC_HAMMING };

/*
Returns a string representation (user-friendly) of the given EC. */
char* ECString(EC);

/*
Find the position of the specified option in the command-line switch vector.
To be a valid switch, there must be nOptionParameters parameters AFTER this switch (options for the specified option).
Returns the position of the option in the vector if found, -1 otherwise.
*/
int a_findCommandLineSwitch(int switchc, char** switchv, const std::string& option, int nOptionParameters);

/*
Read the next up-to-CHAR_LIMIT bytes from the specified file.
Returns the number of bytes read. */
uint a_readBuffer(FILE* file, uch charBuffer[CHAR_LIMIT]);

/*
Write the first charN bytes from the charBuffer to the specified file. */
void a_writeBuffer(FILE* file, uch charBuffer[CHAR_LIMIT], uint charN);