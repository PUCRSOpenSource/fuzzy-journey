#ifndef TABLE_H
#define TABLE_H

#define DEBUG

#include "table_entry.h"
#include <cstdint>
#include <string>
#include <vector>

class Table
{
	public:
		Table();
		~Table();
		void newEntry(std::string description);
		void printMembers(); // For DEBUG.
	private:
		uint32_t code;
		std::vector<TableEntry> entries;
};


#endif /* TABLE_H */
