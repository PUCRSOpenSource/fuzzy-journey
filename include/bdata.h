#ifndef BDATA_H
#define BDATA_H

#include <cstdint>

class BData
{
	public:
		BData(uint32_t index, uint16_t left, uint16_t right);
		~BData();
		uint32_t getIndex();
		uint16_t getLeft();
		uint16_t getRight();
	private:
		uint32_t index;
		uint16_t left;
		uint16_t right;
};

#endif //BDATA_H
