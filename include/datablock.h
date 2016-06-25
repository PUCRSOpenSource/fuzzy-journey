#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <cstdint>
#include "table_entry.h"

#define SIZE 1994 // 2000 - sizeof(address) + sizeof(headerSize);

class DataBlock
{
public:
	DataBlock(uint16_t address);
	DataBlock(uint16_t address, int headerSize, uint8_t data[SIZE]);
	~DataBlock();
	int16_t addEntry(TableEntry entry);
	TableEntry getEntry(int16_t index);
	void remove(int16_t index);
	int16_t getAddress();
	int getHeaderSize();
	uint8_t* getData();

private:
	int16_t address;
	int headerSize;
	uint8_t data[SIZE];

	uint16_t lastHeaderPosition();
	uint16_t lastHeaderSize();
	uint16_t getHeaderPosition(uint16_t index);
	uint16_t getHeaderSize(uint16_t index);
	void saveNewHeader(uint16_t position, uint16_t size);
	void saveNewEntry(uint16_t position, TableEntry entry);
};

#endif //DATABLOCK_H
