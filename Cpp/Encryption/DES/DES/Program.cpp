#include "Common.h"
#include "DESMain.h"

// function declarations

int main()
{
	// Forouzan text
	//ull key = 0xAABB09182736CCDDULL;
	//ull block = 0x123456ABCD132536ULL;
		
	// DES Algorithm Illustrated
	//ull key = 0x133457799BBCDFF1ULL;
	//ull block = 0x0123456789ABCDEFULL;

	// Reverse - Forouzan
	//ull key = 0xAABB09182736CCDDULL;
	//ull block = 0xc0b7a8d05f3a829cULL;

	//ull result = DESBlock(key, block);

	//char i[] = "d:\\users\\zack\\desktop\\in.txt";
	char plaintext[] = "d:\\users\\zack\\desktop\\Shakespeare.txt";
	char cyphertext[] = "d:\\users\\zack\\desktop\\cypher.txt";
	char result[] = "d:\\users\\zack\\desktop\\result.txt";

	ull t = 0xABCDEF1234567890;

	DESFileEncrypt(t, plaintext, cyphertext);
	DESFileDecrypt(t, cyphertext, result);

	return 0;
}



