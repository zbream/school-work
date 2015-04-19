#include <string>
#include "Data.h"

struct BNode
{
	const static int T = 2;

	// record on drive
	int id;
	
	// payload
	int n;
	Data keys[2 * T - 1];
	int children[2 * T];
	
	bool isLeaf;
};