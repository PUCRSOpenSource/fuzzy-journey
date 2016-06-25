#include "btree.h"

BTree::BTree(Node* root)
{
	this->root = root;
}

BTree::~BTree()
{

}

bool BTree::insert(uint32_t index, RowID rowID)
{
	return root->insert(index, rowID);
}

RowID BTree::select(uint32_t index)
{
	return root->select(index);
}