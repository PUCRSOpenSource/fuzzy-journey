#ifndef LEAF_H
#define LEAF_H

#include "node.h"
#include "rowid.h"
#include "ldata.h"
#include <cstdint>
#include <vector>

class Leaf : public Node
{
	public:
		virtual bool insert(uint32_t index, RowID ri);
		virtual RowID select(uint32_t index);

	private:
		std::vector<LData> block;
};

#endif /* LEAF_H */
