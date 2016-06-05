#include "datablock.h"
#include <iostream>

DataBlock::DataBlock(uint16_t address) {
	this->address = address;
	for (int i = 0; i < SIZE; i++) {
		data[i] = i;
	}
	headerSize = 4;
}

DataBlock::~DataBlock() {

}

void DataBlock::addEntry(TableEntry entry) {

}

uint16_t DataBlock::findSpace() {
	std::cout <<
	std::bitset<16>(newHeaderPosition()) <<
	std::endl <<
	std::bitset<16>(newHeaderSize()) <<
	std::endl;
	return 1;
}

uint16_t DataBlock::newHeaderPosition() {
	uint16_t position;
	memcpy(&position, data + headerSize, sizeof(position));
	return position;
}

uint16_t DataBlock::newHeaderSize() {
	uint16_t size;
	memcpy(&size, data + headerSize + 2, sizeof(size));
	return size;
}
