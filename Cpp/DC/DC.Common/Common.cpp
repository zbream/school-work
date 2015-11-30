#include "Common.h"

char* ECString(EC ec)
{
	switch (ec)
	{
	case EC_CRC:
		return "CRC";
	case EC_HAMMING:
		return "Hamming";
	default:
		return "None";
	}
}