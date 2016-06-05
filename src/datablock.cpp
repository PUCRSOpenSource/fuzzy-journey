#include "datablock.h"
#include <iostream>
#include <string>

using namespace std;

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
	// Get position
	uint16_t position = 0;
	uint16_t lastPosition = 0;
	uint16_t lastSize = 0;
	if (headerSize > 0) {
		lastPosition = lastHeaderPosition();
		lastSize = lastHeaderSize();
		position = lastPosition + lastSize;
	}

	// Save stuff
	saveNewHeader(position, entry.size());


	uint8_t *entryData = entry.toByteArray();
	uint16_t actualPosition = SIZE - position - entry.size();
	memcpy(data + actualPosition, entryData, entry.size());
	free(entryData);

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

TableEntry DataBlock::getEntry(uint16_t index) {
	uint32_t entryCode;
	string entryDescription;

	uint16_t position = getHeaderPosition(index);
	uint16_t size = getHeaderSize(index);

	uint16_t actualPosition = SIZE - position - size;

	memcpy(&entryCode, data + actualPosition, sizeof(entryCode));
	memcpy(&entryDescription, data + actualPosition + sizeof(entryCode), size - sizeof(entryCode));
	TableEntry tb(entryCode, entryDescription);
	return tb;
}

uint16_t DataBlock::getHeaderPosition(uint16_t index) {
	uint16_t position;
	memcpy(&position, data + 4 * index, sizeof(position));
	return position;
}

uint16_t DataBlock::getHeaderSize(uint16_t index) {
	uint16_t size;
	memcpy(&size, data + 4 * index + 2, sizeof(size));
	return size;
}
