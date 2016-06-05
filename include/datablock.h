#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <cstdint>

#define SIZE 2000

class DataBlock
{
public:
	DataBlock(uint16_t address);
	~DataBlock();
private:
	uint16_t address;
	uint16_t nextAddress;
	uint8_t data[SIZE];
};

#endif //DATABLOCK_H
