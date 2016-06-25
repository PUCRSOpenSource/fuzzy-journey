#ifndef BTREE_H
#define BTREE_H

#include "node.h"

class BTree
{
	public:
		BTree(Node* root);
		~BTree();
	private:
		Node* root;
};

#endif /* BTREE_H */
