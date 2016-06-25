#include "leaf.h"
#include <iostream>

bool Leaf::insert(uint32_t index, RowID rowID)
{
	for(size_t i = 0; i < block.size(); i++)
	{
		if (index == block[i].getIndex()) {
			return false;
		}
		if (index > block[i].getIndex()) {
			block.insert(block.begin() + i, LData(index, rowID));
			return true;
		}
	}

	return false;
}

RowID Leaf::select(uint32_t index)
{
	return RowID();
}
