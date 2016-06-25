#include "branch.h"
#include <iostream>

bool Branch::insert(uint32_t index, RowID ri)
{
	std::cout << "Branch: insert" << std::endl;
	return false;
}

RowID Branch::select(uint32_t index)
{
	return RowID();
}
