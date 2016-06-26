#include "btree.h"

BTree::BTree(Node* root)
{
	this->root = root;
}

BTree::~BTree()
{
	delete root;
}

bool BTree::insert(uint32_t index, RowID rowID)
{
	root = root->insert(index, rowID);
	return true;
}

RowID BTree::select(uint32_t index)
{
	return root->select(index);
}

bool BTree::hasIndex(uint32_t index)
{
	return root->hasIndex(index);
}

bool BTree::update(uint32_t index, RowID rowID)
{
	return root->update(index, rowID);
}

Node* BTree::getRoot()
{
	return root;
}

void BTree::print()
{
	root->print("");
}

std::vector<RowID> BTree::selectAll()
{
	return root->selectAll();
}
