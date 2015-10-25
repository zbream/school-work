#include "Common.h"

// Performs AES's SubBytes transformation.
void t_SubBytes(uch state[4][4]);

// Performs AES's Inverse SubBytes transformation.
void t_InvSubBytes(uch state[4][4]);

// Returns AES's SubBytes substitution for the specified byte.
uch t_SubBytesSubstitution(uch in);

// Returns AES's Inverse SubBytes substitution for the specified byte.
uch t_InvSubBytesSubstitution(uch in);

// Performs AES's ShiftRows transformation.
void t_ShiftRows(uch state[4][4]);

// Performs AES's Inverse ShiftRows transformation.
void t_InvShiftRows(uch state[4][4]);

// Performs AES's MixColumns transformation.
void t_MixColumns(uch state[4][4]);

// Performs AES's Inverse MixColumns transformation.
void t_InvMixColumns(uch state[4][4]);

// Performs AES's AddRoundKey transformation, using the specified key.
void t_AddRoundKey(uch state[4][4], uch key[4][4]);