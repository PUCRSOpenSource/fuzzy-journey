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
		virtual bool hasIndex(uint32_t index);
		virtual bool update(uint32_t index, RowID rowID);
		void addToBlock(BData data);
		void setBlock(std::vector<BData> block);
		virtual int myClass();
		void split();
		virtual void print(std::string level);
		virtual void setParent(Node *parent);
		virtual Node* getParent();
		void changeChildParent(Node* parent);
		virtual std::vector<RowID> selectAll();

	private:
		std::vector<BData> block;
};

#endif /* BRANCH_H */
