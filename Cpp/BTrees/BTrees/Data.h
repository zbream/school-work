/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

Data.h
Holds a single key/count pair, which move together as one in the BTree implementation.
*/

#include <string>

struct Data
{
	std::string key;
	int count;
};