#include "Common.h"
#include "DESMain.h"

// function declarations

int main()
{
	// Forouzan text
	ull key = 0xAABB09182736CCDDULL;
	ull block = 0x123456ABCD132536ULL;
		
	// DES Algorithm Illustrated
	//ull key = 0x133457799BBCDFF1ULL;
	//ull block = 0x0123456789ABCDEFULL;

	// Reverse - Forouzan
	//ull key = 0xAABB09182736CCDDULL;
	//ull block = 0xc0b7a8d05f3a829cULL;

	ull result = DESBlock(key, block);

	return 0;
}



