#include "leaf.h"
#include <iostream>

bool Leaf::insert(uint32_t index, RowID ri)
{
	std::cout << "Leaf: insert" << std::endl;
	return false;
}

RowID Leaf::select(uint32_t index)
{
	return RowID();
}
