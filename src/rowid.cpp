#include "rowid.h"

RowID::RowID(int16_t blockNumber, int16_t position)
{
	this->blockNumber = blockNumber;
	this->position = position;
}

RowID::~RowID()
{

}

int16_t RowID::getBlockNumber()
{
	return blockNumber;
}

int16_t RowID::getPosition()
{
	return position;
}
