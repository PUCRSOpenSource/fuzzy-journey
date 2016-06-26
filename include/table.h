#ifndef TABLE_H
#define TABLE_H

#include "table_entry.h"
#include "buffer.h"
#include "rowid.h"
#include "btree.h"
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>

class Table
{
	public:
		~Table();
		RowID newEntry(uint32_t code, std::string description);
		TableEntry getEntry(uint32_t code);
		void remove(uint32_t code);
		RowID update(uint32_t code, std::string description);
		void printBTree();
		void saveData();
		static Table* getInstance();

	private:
		Table();
		Buffer buffer;
		BTree* btree;
		static Table* t_Instance;
};


#endif /* TABLE_H */
