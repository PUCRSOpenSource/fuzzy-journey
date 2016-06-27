#include "branch.h"
#include <iostream>

Node* Branch::insert(uint32_t index, RowID ri)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if (index < block[i].getIndex())
		{
			block[i].setLeft(block[i].getLeft()->insert(index, ri));
			return this;
		}

		if (i == block.size() - 1) // If last and not grater or equal
		{
			block[i].setRight(block[i].getRight()->insert(index,ri));
			return this;
		}

	}

	return this;
}

RowID Branch::select(uint32_t index)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if (index < block[i].getIndex())
		{
			return block[i].getLeft()->select(index);
		}
	}
	return block.back().getRight()->select(index);
}

bool Branch::hasIndex(uint32_t index)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if (index < block[i].getIndex())
		{
			return block[i].getLeft()->hasIndex(index);
		}
	}
	return block.front().getRight()->hasIndex(index);
}

bool Branch::update(uint32_t index, RowID rowID)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if (index < block[i].getIndex())
		{
			return block[i].getLeft()->update(index, rowID);
		}
	}
	return block.front().getRight()->update(index, rowID);
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

	if (block.size() > max_size)
	{
		split();
	}
}

void Branch::split()
{
	size_t const half_size = block.size() / 2;
	std::vector<BData> left_block(block.begin(), block.begin() + half_size);
	std::vector<BData> right_block(block.begin() + half_size, block.end());

	BData bData = right_block[0];
	right_block.erase(right_block.begin());


	Branch* newBranchLeft = new Branch();
	newBranchLeft->setBlock(left_block);
	newBranchLeft->changeChildParent(newBranchLeft);

	Branch* newBranchRight = new Branch();
	newBranchRight->setBlock(right_block);
	newBranchRight->changeChildParent(newBranchRight);

	if (!parent)
	{
		newBranchLeft->setParent(this);
		newBranchRight->setParent(this);

		bData.setLeft(newBranchLeft);
		bData.setRight(newBranchRight);

		std::vector<BData> my_block;
		my_block.push_back(bData);
		setBlock(my_block);
	}
	else
	{
		newBranchLeft->setParent(parent);
		newBranchRight->setParent(parent);

		bData.setLeft(newBranchLeft);
		bData.setRight(newBranchRight);

		Branch* p = (Branch*) parent;
		p->addToBlock(bData);
	}

}

void Branch::changeChildParent(Node* parent)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		block[i].getLeft()->setParent(parent);

		if (i == block.size() - 1) // If last and not grater or equal
		{
			block[i].getRight()->setParent(parent);
		}
	}
}

void Branch::setParent(Node* parent)
{
	this->parent = parent;
}

Node* Branch::getParent()
{
	return parent;
}

void Branch::setBlock(std::vector<BData> block)
{
	this->block = block;
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

std::string Branch::graphPrint()
{
	std::ostringstream ss("");
	ss << "node";
	ss << getName();
	ss << "[label = \"";

	unsigned int i = 0;
	for (auto &bd : block)
	{
		ss << "<f" << i << "> |" << bd.getIndex() << "|";
		i++;
	}
	ss << "<f" << i << ">\"];" << std::endl;


	for (i = 0; i < block.size(); i++)
	{
		ss << block[i].getLeft()->graphPrint();
		ss << "\"node" << getName() << "\"";
		ss << ":f" << i << " -> " << "\"node";
		ss << block[i].getLeft()->getName() << "\"" << std::endl;

		if (i == block.size() - 1) // If last call right
		{
			ss << block[i].getRight()->graphPrint();
			ss << "\"node" << getName() << "\"";
			ss << ":f" << i + 1 << " -> " << "\"node";
			ss << block[i].getRight()->getName() << "\"" << std::endl;
		}
	}

	return ss.str();
}

std::string Branch::getName()
{
	std::ostringstream ss("");
	ss << block[0].getIndex() << "b";
	return ss.str();
}

std::vector<RowID> Branch::selectAll()
{
	std::vector<RowID> rowIds;
	for (size_t i = 0; i < block.size(); i++) {
		std::vector<RowID> leftIds = block[i].getLeft()->selectAll();
		rowIds.insert(rowIds.end(), leftIds.begin(), leftIds.end());
		if(i == block.size() - 1)
		{
			std::vector<RowID> rightIds = block[i].getRight()->selectAll();
			rowIds.insert(rowIds.end(), rightIds.begin(), rightIds.end());
		}
	}
	return rowIds;

}
