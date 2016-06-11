#ifndef TABLE_H
#define TABLE_H

#include "table_entry.h"
#include "buffer.h"
#include "rowid.h"
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>

class Table
{
	public:
		Table();
		~Table();
		RowID newEntry(std::string description);
		// This functions will be different, needs to get Entry from key, but needs BTree for that.
		TableEntry getEntry(RowID rowID);
		void remove(RowID rowID);
		RowID update(RowID rowID, std::string description);
		void loadCode();
		void saveCode();
		void initCode();

	private:
		uint32_t code;
		Buffer buffer;
};


#endif /* TABLE_H */
