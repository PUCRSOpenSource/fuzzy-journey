#include "branch.h"
#include <iostream>

Node* Branch::insert(uint32_t index, RowID ri)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if (block[i].getIndex() >= index)
			return block[i].getLeft()->insert(index, ri);

		if (i == block.size() - 1) // If last and not grater or equal
			return block[i].getRight()->insert(index,ri);
	}

	return this;
}

RowID Branch::select(uint32_t index)
{
	return RowID();
}

void Branch::addToBlock(BData data)
{

	for(size_t i = 0; i < block.size(); i++)
	{
		if (i > block[i].getIndex())
		{
			block.insert(block.begin() + i, data);
		}
	}

	block.push_back(data);
}

int Branch::myClass()
{
	return 1;
}

void Branch::print(std::string level)
{
	std::cout << level << "Branch" << std::endl;
	level += "  ";
	for (unsigned int i = 0; i < block.size(); i++)
	{
		std::cout << level << block[i].getIndex() << std::endl;
		block[i].getLeft()->print(level);

		if (i == block.size() - 1) // If last call right
			block[i].getRight()->print(level);
	}
}
