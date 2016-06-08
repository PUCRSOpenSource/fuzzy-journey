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

RowID Table::newEntry(std::string description)
{
	TableEntry entry(code, description);
	RowID rowID = buffer.newEntry(entry);
	std::cout <<
			"Now I would add to the tree an object with rowID = " <<
			rowID.getBlockNumber() <<
			";" <<
			rowID.getPosition() <<
			std::endl;
	code++;
	return rowID;
}

TableEntry Table::getEntry(RowID rowID)
{
	TableEntry entry = buffer.getEntry(rowID);
	std::cout <<
	"Now I would get an entry with code: " <<
	entry.getCode() <<
	" - and description :" <<
	entry.getDescription() <<
	std::endl;
	return entry;
}

