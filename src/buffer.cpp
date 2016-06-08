#include "buffer.h"

Buffer::Buffer()
{
	// Fake initialization:
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

