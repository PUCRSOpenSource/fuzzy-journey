#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include "rowid.h"
#include <vector>

class BTree
{
	public:
		BTree(Node* root);
		~BTree();
		bool insert(uint32_t index, RowID rowID);
		RowID select(uint32_t index);
		bool hasIndex(uint32_t index);
		std::vector<RowID> selectAll();
		Node* getRoot();
		void print();
		bool update(uint32_t index, RowID rowID);
	private:
		Node* root;
};

#endif /* BTREE_H */
