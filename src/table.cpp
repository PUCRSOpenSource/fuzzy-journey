#include "table.h"
#include "table_entry.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

Table::Table(BTree* btree)
{
	this->btree = btree;
}

Table::~Table()
{

}

RowID Table::newEntry(uint32_t code, std::string description)
{
	if (btree->hasIndex(code)) {
		throw std::runtime_error( "Primary key already exists" );
	}
	TableEntry entry(code, description);
	RowID rowID = buffer.newEntry(entry);
	btree->insert(code, rowID);
	code++;
	return rowID;
}

TableEntry Table::getEntry(uint32_t code)
{
	RowID rowID = btree->select(code);
	TableEntry entry = buffer.getEntry(rowID);
	return entry;
}

void Table::remove(uint32_t code)
{
	RowID rowID = btree->select(code);
	TableEntry entry = buffer.getEntry(rowID);
	buffer.remove(rowID);
}

RowID Table::update(uint32_t code, std::string description)
{
	TableEntry entry = getEntry(code);
	remove(code);
	entry.setDescription(description);
	RowID newRowID = buffer.newEntry(entry);
	return newRowID;
}

void Table::saveData()
{
	buffer.saveData();
}
