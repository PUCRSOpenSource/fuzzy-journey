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
		// This function will probably be a little different:
		TableEntry getEntry(RowID rowID);
	private:
		uint32_t code;
		Buffer buffer;
};


#endif /* TABLE_H */
