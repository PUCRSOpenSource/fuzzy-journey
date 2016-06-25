#ifndef BDATA_H
#define BDATA_H

#include <cstdint>
#include "node.h"

class BData
{
	public:
		BData(uint32_t index, Node* left, Node* right);
		~BData();
		uint32_t getIndex();
		Node* getLeft();
		Node* getRight();
	private:
		uint32_t index;
		Node* left;
		Node* right;
};

#endif //BDATA_H
