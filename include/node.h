#ifndef NODE_H
#define NODE_H

#include "rowid.h"
#include <cstdint>
#include <string>

class Node
{
	public:
		virtual ~Node() {}
		virtual Node* insert(uint32_t index, RowID ri) = 0;
		virtual RowID select(uint32_t index) = 0;
		virtual int myClass() = 0;
		virtual void print(std::string level) = 0;

	protected:
		Node* parent = nullptr;
		int max_size = 2;
};

#endif /* NODE_H */
