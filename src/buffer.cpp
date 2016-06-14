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
	FILE* ptr_myDataBlock = fopen("datafile.part", "r+b");
	fseek(ptr_myDataBlock, index * DATABLOCK_SIZE + sizeof(int16_t), SEEK_SET);
	int header_size_aux;
	uint8_t* data_aux = static_cast<uint8_t*>(malloc(SIZE));
	fread(&header_size_aux, sizeof(int), 1, ptr_myDataBlock);
	fread(data_aux, sizeof(uint8_t), SIZE, ptr_myDataBlock);
	datablocks.push_back(DataBlock(index, header_size_aux, data_aux));
	fclose(ptr_myDataBlock);
}

void Buffer::saveDatablock(DataBlock datablock)
{
	FILE* ptr_myDataBlock = fopen("datafile.part", "r+");
	fseek(ptr_myDataBlock, datablock.getAddress() * DATABLOCK_SIZE, SEEK_SET);
	int16_t addr_aux = datablock.getAddress();
	int header_size_aux = datablock.getHeaderSize();
	uint8_t* data_aux = datablock.getData();
	fwrite(&addr_aux, sizeof(int16_t), 1, ptr_myDataBlock);
	fwrite(&header_size_aux, sizeof(int), 1, ptr_myDataBlock);
	fwrite(data_aux, sizeof(uint8_t), SIZE, ptr_myDataBlock);
	fclose(ptr_myDataBlock);
}

void Buffer::saveData() {
	for (auto &datablock : datablocks) {
		saveDatablock(datablock);
	}
}
