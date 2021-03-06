#ifndef NODE_H
#define NODE_H

#include "rowid.h"
#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

class Node
{
	public:
		virtual ~Node() {}
		virtual Node* insert(uint32_t index, RowID ri) = 0;
		virtual RowID select(uint32_t index) = 0;
		virtual bool hasIndex(uint32_t index) = 0;
		virtual bool update(uint32_t index, RowID rowID) = 0;
		virtual int myClass() = 0;
		virtual void print(std::string level) = 0;
		virtual std::string graphPrint() = 0;
		virtual void setParent(Node *parent) = 0;
		virtual Node* getParent() = 0;
		virtual std::vector<RowID> selectAll() = 0;
		virtual std::string getName() = 0;

	protected:
		Node* parent = nullptr;
		uint32_t max_size = 250;
};

#endif /* NODE_H */
