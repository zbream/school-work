#include "Common.h"

void t_SubBytes(uch state[4][4]);
void t_InvSubBytes(uch state[4][4]);
uch t_SubBytesSubstitution(uch in);
uch t_InvSubBytesSubstitution(uch in);

void t_ShiftRows(uch state[4][4]);
void t_InvShiftRows(uch state[4][4]);

void t_MixColumns(uch state[4][4]);
void t_InvMixColumns(uch state[4][4]);

void t_AddRoundKey(uch state[4][4], uch key[4][4]);