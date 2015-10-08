#include "Common.h"

uint l_prepareFrame(uch charBuffer[CHAR_LIMIT], uint charN, uch frameBuffer[CHAR_LIMIT + 3]);
uint l_prepareTransmit(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch transmitBuffer[(CHAR_LIMIT + 3) * 8]);
uint l_parseTransmit(uch transmitBuffer[(CHAR_LIMIT + 3) * 8], uint transmitN, uch frameBuffer[CHAR_LIMIT + 3]);
uint l_parseFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch charBuffer[CHAR_LIMIT]);
bool l_validateFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN);