#include "table.h"
#include "table_entry.h"
#include <iostream>

Table::Table()
{
	code = 0;
}

Table::~Table()
{

}

void Table::newEntry(std::string description)
{
	TableEntry te(code, description);
	entries.push_back(te);
	code++;
}

// For DEBUG.
void Table::printMembers()
{
	for (uint32_t i = 0; i < entries.size(); i++)
	{
		std::cout << "Element: " << i << std::endl;
		std::cout << "Code: " << entries[i].getCode() << std::endl;
		std::cout << "Description: " << entries[i].getDescription() << std::endl;
		std::cout << std::endl;
	}
}

