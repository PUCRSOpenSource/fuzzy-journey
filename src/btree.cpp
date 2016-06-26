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

Node* BTree::getRoot()
{
	return root;
}