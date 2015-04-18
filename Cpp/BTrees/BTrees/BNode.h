#include <string>
#include "Data.h"

struct BNode
{
	const static int T = 3;

	// record on drive
	int id;
	
	// payload
	int n;
	Data keys[T];
	int children[T + 1];
	
	bool isLeaf;
};