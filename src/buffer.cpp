#include "buffer.h"

Buffer::Buffer()
{
	// Fake initialization, remove when fetch from file is done:
	DataBlock datablock(0);
	datablocks.push_back(datablock);

}

Buffer::~Buffer()
{

}

RowID Buffer::newEntry(TableEntry entry)
{
	for (auto &datablock : datablocks) {
		int16_t result = datablock.addEntry(entry);
		if (result >= 0) {
			return RowID(datablock.getAddress(), result);
		}
	}

	//If gets here all datablocks are full, Fetch new datablock

	//TODO: handle this better
	return RowID(-1,-1);
}

TableEntry Buffer::getEntry(RowID rowID)
{
	for (auto &datablock : datablocks) {
		if (datablock.getAddress() == rowID.getBlockNumber()) {
			return datablock.getEntry(rowID.getPosition());
		}
	}

	//If gets here is cache miss, load datablock from memory

	//TODO: handle this better
	return TableEntry(123, "error");
}

void Buffer::loadDatablock(int16_t index)
{
	//TODO: load datablock from datafile
	// datablock consists of 2000 bytes.
	// first 4 bytes go to variable address.
	// Important: address needs to match position in datablock(it will be 0, set it manually)
	// (eg. first 2000 bytes address 0, next 2000 bytes address 1, etc)
	// next 4 bytes go to variable headerSize.
	// rest goes to data variable.
	// After that add datafile to vector.
	// If vector is full(see capacity at github) remove the first one that was added.
	// When this is ready remove code from initializer xD

}

void Buffer::saveDatablock(DataBlock datablock)
{
	// This will only happen when a datablock is removed from vector
	// Or when we tell it to, idk
}
