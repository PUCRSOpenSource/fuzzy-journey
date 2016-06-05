#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <cstdint>

#define DATA_SIZE 1960
#define OVERHEAD_SIZE 36

class DataBlock
{
public:
	DataBlock(uint16_t address);
	~DataBlock();
private:
	uint16_t address;
	uint16_t nextAddress;
	uint8_t entryInfo[OVERHEAD_SIZE];
	uint8_t tableEntries[DATA_SIZE];
};

#endif //DATABLOCK_H
