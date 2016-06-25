#include "bdata.h"

BData::BData(uint32_t index, uint16_t left, uint16_t right)
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

uint16_t BData::getLeft()
{
	return left;
}

uint16_t BData::getRight()
{
	return right;
}