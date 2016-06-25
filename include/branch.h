#ifndef BRANCH_H
#define BRANCH_H

#include "node.h"
#include "rowid.h"
#include <cstdint>

class Branch : public Node
{
	public:
		virtual bool insert(uint32_t index, RowID ri);
		virtual RowID select(uint32_t index);
};

#endif /* BRANCH_H */
