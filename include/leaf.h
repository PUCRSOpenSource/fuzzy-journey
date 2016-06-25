#ifndef LEAF_H
#define LEAF_H

#include "node.h"
#include "rowid.h"
#include <cstdint>

class Leaf : public Node
{
	public:
		virtual bool insert(uint32_t index, RowID ri);
		virtual RowID select(uint32_t index);
};

#endif /* LEAF_H */
