#include "bdata.h"

BData::BData(uint32_t index, Node* left, Node* right)
{
	this->index = index;
	this->left = left;
	this->right = right;
}

BData::~BData()
{

}

uint32_t BData::getIndex()
{
	return index;
}

Node* BData::getLeft()
{
	return left;
}

Node* BData::getRight()
{
	return right;
}