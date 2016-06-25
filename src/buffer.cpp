#include "buffer.h"

Buffer::Buffer()
{

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

	uint16_t index = chooseDatablock();
	loadDatablock(index);
	return newEntry(entry);
}

TableEntry Buffer::getEntry(RowID rowID)
{
	for (auto &datablock : datablocks) {
		if (datablock.getAddress() == rowID.getBlockNumber()) {
			return datablock.getEntry(rowID.getPosition());
		}
	}

	loadDatablock(rowID.getBlockNumber());
	return getEntry(rowID);
}

void Buffer::remove(RowID rowID)
{
	for (auto &datablock : datablocks) {
		if (datablock.getAddress() == rowID.getBlockNumber()) {
			datablock.remove(rowID.getPosition());
			return;
		}
	}

	loadDatablock(rowID.getBlockNumber());
	remove(rowID);
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
	if (datablocks.size() > FRAMES)
	{
		DataBlock last = datablocks.front();
		saveDatablock(last);
		datablocks.pop_front();
	}
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

void Buffer::saveData()
{
	for (auto &datablock : datablocks)
	{
		saveDatablock(datablock);
	}
}

int16_t Buffer::chooseDatablock()
{
	for (uint16_t i = 0; i < DATABLOCKS_TOTAL; i++) {
		if (!isLoaded(i)) {
			return i;
		}
	}
	return -1;
}

bool Buffer::isLoaded(uint16_t index)
{
	for (auto &datablock : datablocks) {
		if (datablock.getAddress() == index) {
			return true;
		}
	}
	return false;
}
