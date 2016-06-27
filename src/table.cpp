#include "table.h"
#include "table_c.h"
#include "table_entry.h"
#include "leaf.h"
#include "btree.h"
#include "datafile.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <ctime>

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

	srand(time(0));

	btree = new BTree(new Leaf());
	loadBTreeData();
}

Table::~Table()
{

}

RowID Table::insert(uint32_t code, std::string description)
{
	if (btree->hasIndex(code)) {
		throw std::runtime_error( "Primary key already exists." );
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

std::string Table:: printGraph()
{
	return btree->graphPrint();
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
	throw std::runtime_error( "Not found." );
}

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

static int stringLength = sizeof(alphanum) - 1;

static std::string genRandomStr()
{
	std::string str;
	for (uint32_t i = 0; i < 15; i++)
	{
		str += alphanum[rand() % stringLength];
	}
	return str;
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
	try {
		TableEntry te = ((Table*)table)->select(code);
		std::cout << "Code: " << te.getCode() << std::endl;
		std::cout << "Description: " << te.getDescription() << std::endl;
	} catch(const std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
}



void insertNTable(void* table, uint32_t n)
{
	for (uint32_t i = 0; i < n; i++)
	{
		try {
			((Table*)table)->insert(i, genRandomStr());
		} catch(const std::exception & ex) {
			n++;
		}
	}
}

void updateTable(void* table, uint32_t code, char* description)
{
	try {
		std::string str(description);
		((Table*)table)->update(code, str);
	} catch(const std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void selectDTable(void* table, char* description)
{
	try {
		std::string str(description);
		TableEntry te = ((Table*)table)->select(str);
		std::cout << "Code: " << te.getCode() << std::endl;
		std::cout << "Description: " << te.getDescription() << std::endl;
	} catch(const std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void printTableGraph(void* table)
{
	std::ofstream out("graphTree");
	out << ((Table*)table)->printGraph();
	out.close();
	system("dot -T png graphTree -o gt.png; feh gt.png");
}
