/* Ream, Zack - One Way Hash (SHA-256)
EECS 3540 - 3/17/2016 */

#pragma once

#include "Common.h"

void initializeHash(uint H[8]);

void performHashOnChunk(uint H[8], const uint M[16]);
