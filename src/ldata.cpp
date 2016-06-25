#include "ldata.h"

LData::LData(uint32_t index, RowID rowID)
{
	this->index = index;
	this->rowID = rowID;
}

LData::~LData()
{

}

uint32_t LData::getIndex()
{
	return index;
}

RowID LData::getRowID()
{
	return rowID;
}
