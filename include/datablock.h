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

private:
	int address;
	int headerSize;
	uint8_t data[SIZE];

	uint16_t lastHeaderPosition();
	uint16_t lastHeaderSize();
	void saveNewHeader(uint16_t position, uint16_t size);
};

#endif //DATABLOCK_H
