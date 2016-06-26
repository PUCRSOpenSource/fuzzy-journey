#include "table.h"
#include "table_c.h"
#include "table_entry.h"
#include "leaf.h"
#include "btree.h"
#include "datafile.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

Table* Table::t_Instance;

Table* Table::getInstance()
{
	if (!t_Instance)
		t_Instance = new Table;

	return t_Instance;
}

Table::Table()
{
	std::ifstream ifile("datafile.part");
	if (!ifile)
		Datafile::init();

	btree = new BTree(new Leaf());
	loadBTreeData();
}

Table::~Table()
{

}

RowID Table::insert(uint32_t code, std::string description)
{
	if (btree->hasIndex(code)) {
		throw std::runtime_error( "Primary key already exists" );
	}
	TableEntry entry(code, description);
	RowID rowID = buffer.newEntry(entry);
	btree->insert(code, rowID);
	return rowID;
}

TableEntry Table::select(uint32_t code)
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

void Table::update(uint32_t code, std::string description)
{

	TableEntry entry(code, description);
	RowID rowID = buffer.newEntry(entry);
	btree->update(code, rowID);
}

void Table::saveData()
{
	buffer.saveData();
}

void Table::printBTree()
{
	btree->print();
}

void Table::loadBTreeData()
{
	std::vector<LData> entries = buffer.allEntries();
	for(size_t i = 0; i < entries.size(); i++)
	{
		uint32_t index = entries[i].getIndex();
		RowID id = entries[i].getRowID();
		btree->insert(index, id);
	}

}

TableEntry Table::select(std::string description)
{
	std::vector<RowID> rowIDs = btree->selectAll();

	for (unsigned int i = 0; i < rowIDs.size(); i++)
	{
		TableEntry entry = buffer.getEntry(rowIDs[i]);
		if (entry.getDescription().compare(description) == 0)
			return entry;
	}
	throw std::runtime_error( "Not found" );
}

void* getTable()
{
	return (void*) Table::getInstance();
}

void printTableTree(void* table)
{
	((Table*)table)->printBTree();
}

void insertTable(void* table, uint32_t code, char* description)
{
	try {
		std::string str(description);
		((Table*)table)->insert(code, str);
	} catch(const std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void saveTableData(void* table)
{
	((Table*)table)->saveData();
}

void selectTable(void* table, uint32_t code)
{
	TableEntry te = ((Table*)table)->select(code);
	std::cout << "Code: " << te.getCode() << std::endl;
	std::cout << "Description: " << te.getDescription() << std::endl;
}
