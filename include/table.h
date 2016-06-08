#ifndef TABLE_H
#define TABLE_H

#include "table_entry.h"
#include "buffer.h"
#include "rowid.h"
#include <cstdint>
#include <string>
#include <vector>

class Table
{
	public:
		Table();
		~Table();
		RowID newEntry(std::string description);
		// This function will be different, needs to get Entry from key, but needs BTree for that.
		TableEntry getEntry(RowID rowID);
	private:
		uint32_t code;
		Buffer buffer;
};


#endif /* TABLE_H */
