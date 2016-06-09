#include "buffer.h"

Buffer::Buffer()
{
	loadDatablock(0);
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

void Buffer::remove(RowID rowID)
{
	for (auto &datablock : datablocks) {
		if (datablock.getAddress() == rowID.getBlockNumber()) {
			datablock.remove(rowID.getPosition());
		}
	}

	// If gets here is cache miss, load datablock from memory
}

void Buffer::loadDatablock(int16_t index)
{
	FILE* ptr_myDataBlock = fopen("datafile.part", "rb");
	fseek(ptr_myDataBlock, index * DATABLOCK_SIZE, SEEK_SET);
	int16_t addr_aux;
	int header_size_aux;
	uint8_t* data_aux = static_cast<uint8_t*>(malloc(SIZE));
	fread(&addr_aux, sizeof(int16_t), 1, ptr_myDataBlock);
	fread(&header_size_aux, sizeof(int), 1, ptr_myDataBlock);
	fread(data_aux, SIZE, 1, ptr_myDataBlock);
	datablocks.push_back(DataBlock(addr_aux, header_size_aux, data_aux));
	fclose(ptr_myDataBlock);
}

void Buffer::saveDatablock(DataBlock datablock)
{
	// This will only happen when a datablock is removed from vector
	// Or when we tell it to, idk
}
