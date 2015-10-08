#include "Common.h"

uint l_prepareFrame(uch charBuffer[CHAR_LIMIT], uint charN, uch frameBuffer[CHAR_LIMIT + 3]);
uint l_prepareTransmission(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch transmissionBuffer[(CHAR_LIMIT + 3) * 8]);
uint l_parseTransmission(uch transmissionBuffer[(CHAR_LIMIT + 3) * 8], uint transmissionN, uch frameBuffer[CHAR_LIMIT + 3]);
uint l_parseFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch charBuffer[CHAR_LIMIT]);
bool l_validateFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN);