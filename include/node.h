#ifndef NODE_H
#define NODE_H

#include "rowid.h"
#include <cstdint>

class Node
{
	public:
		virtual ~Node() {}
		virtual bool insert(uint32_t index, RowID ri) = 0;
		virtual RowID select(uint32_t index) = 0;

	private:
		int max_size;
};

#endif /* NODE_H */
