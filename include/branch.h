#ifndef BRANCH_H
#define BRANCH_H

#include "node.h"
#include "rowid.h"
#include "bdata.h"
#include <cstdint>
#include <vector>

class Branch : public Node
{
	public:
		virtual Node* insert(uint32_t index, RowID ri);
		virtual RowID select(uint32_t index);
		void addToBlock(BData data);
		virtual int myClass();

	private:
		std::vector<BData> block;
};

#endif /* BRANCH_H */
