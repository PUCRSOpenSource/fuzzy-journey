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
	uint16_t findSpace();
	uint16_t newHeaderPosition();
	uint16_t newHeaderSize();

private:
	int address;
	int headerSize;

	uint8_t data[SIZE];
};

#endif //DATABLOCK_H
