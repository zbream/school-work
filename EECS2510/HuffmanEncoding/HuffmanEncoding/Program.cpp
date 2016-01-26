/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include <iostream>
#include <string>
#include "Huffman.h"

using namespace std;

int main()
{
	string src = "Shakespeare.txt";
	string enc = "Shakespeare.enc";
	string dec = "Shakespeare.dec";

	Huffman hf;

	hf.InitializeFromFile(src);
	cout << endl;

	hf.EncodeFile(src, enc);
	cout << endl;

	hf.DecodeFile(enc, dec);
	cout << endl;

	cout << "Press Enter to exit.";
	cin.get();
	return 0;
}