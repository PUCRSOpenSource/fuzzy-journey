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
		Table(BTree* btree);
		~Table();
		RowID newEntry(std::string description);
		TableEntry getEntry(uint32_t code);
		void remove(uint32_t code);
		RowID update(uint32_t code, std::string description);

		void saveData();

	private:
		uint32_t code;
		Buffer buffer;
		BTree* btree;
		void loadCode();
		void saveCode();
		void initCode();
};


#endif /* TABLE_H */
