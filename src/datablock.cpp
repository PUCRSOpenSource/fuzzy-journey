#include "datablock.h"
#include <iostream>

DataBlock::DataBlock(uint16_t address) {
	this->address = address;
	for (int i = 0; i < SIZE; i++) {
		data[i] = 0;
	}
	headerSize = 0;
}

DataBlock::~DataBlock() {

}

void DataBlock::addEntry(TableEntry entry) {
	saveNewHeader(1, 1);

	uint16_t lastPosition = lastHeaderPosition();
	uint16_t lastSize = lastHeaderSize();
//	uint16_t position = lastPosition + lastSize;

	std::cout <<
	std::bitset<16>(lastPosition) <<
	std::endl <<
	std::bitset<16>(lastSize) <<
	std::endl;

}

uint16_t DataBlock::lastHeaderPosition() {
	uint16_t position;
	memcpy(&position, data + headerSize - 4, sizeof(position));
	return position;
}

uint16_t DataBlock::lastHeaderSize() {
	uint16_t size;
	memcpy(&size, data + headerSize - 2, sizeof(size));
	return size;
}

void DataBlock::saveNewHeader(uint16_t position, uint16_t size) {
	memcpy(data + headerSize, &position, sizeof(uint16_t));
	memcpy(data + headerSize + 2, &size, sizeof(uint16_t));
	headerSize += 4;
}
