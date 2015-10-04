#include "Common.h"

uch l_prepareFrame(uch charBuffer[CHAR_LIMIT], uch charN, uch frameBuffer[3 + (8 * CHAR_LIMIT)]);
uch l_parseFrame(uch frameBuffer[3 + 8 * CHAR_LIMIT], uch frameN, uch charBuffer[CHAR_LIMIT]);
bool l_validateFrame(uch frameBuffer[3 + 8 * CHAR_LIMIT], uch frameN);