#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <cstdint>
#include "table_entry.h"

#define SIZE 2000

class DataBlock {
public:
	DataBlock(uint16_t address);
	~DataBlock();
	void addEntry(TableEntry entry);
	TableEntry getEntry(uint16_t index);

private:
	int address;
	int headerSize;
	uint8_t data[SIZE];

	uint16_t lastHeaderPosition();
	uint16_t lastHeaderSize();
	uint16_t getHeaderPosition(uint16_t index);
	uint16_t getHeaderSize(uint16_t index);
	void saveNewHeader(uint16_t position, uint16_t size);
};

#endif //DATABLOCK_H
