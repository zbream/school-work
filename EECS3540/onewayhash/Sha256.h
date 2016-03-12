#pragma once

#include "Common.h"

void initializeHash(uint H[8]);

void performHashOnChunk(uint H[8], const uint M[16]);
