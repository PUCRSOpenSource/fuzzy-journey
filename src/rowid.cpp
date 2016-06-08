#include "rowid.h"

RowID::RowID(int32_t blockNumber, int32_t position)
{
	this->blockNumber = blockNumber;
	this->position = position;
}

RowID::~RowID()
{

}

int32_t RowID::getBlockNumber()
{
	return blockNumber;
}

int32_t RowID::getPosition()
{
	return position;
}
