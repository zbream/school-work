#include <string>
#include "Data.h"

struct BNode
{
	const static int T = 3;
	
	int n;
	Data keys[T];
	int children[T + 1];
	
	bool isLeaf;
};