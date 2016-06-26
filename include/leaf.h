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
		virtual Node* insert(uint32_t index, RowID rowID);
		virtual RowID select(uint32_t index);
		Node* split();
		virtual int myClass();

	private:
		std::vector<LData> block;
};

#endif /* LEAF_H */
