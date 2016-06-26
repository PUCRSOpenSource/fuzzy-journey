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
		// This functions will be different, needs to get Entry from key, but needs BTree for that.
		TableEntry getEntry(RowID rowID);
		void remove(RowID rowID);
		RowID update(RowID rowID, std::string description);

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
