#include "table.h"
#include "table_entry.h"
#include <iostream>
#include <fstream>

Table::Table(BTree* btree)
{
	std::ifstream ifile("tabledata.bin");
	if (!ifile)
		initCode();
	loadCode();
	this->btree = btree;
}

Table::~Table()
{

}

RowID Table::newEntry(std::string description)
{
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

void Table::loadCode()
{
	FILE* dataPointer = fopen("tabledata.bin", "r+b");
	fread(&code, sizeof(uint32_t), 1, dataPointer);
	fclose(dataPointer);
}

void Table::saveCode()
{
	FILE* dataPointer = fopen("tabledata.bin", "r+");
	fwrite(&code, sizeof(uint32_t), 1, dataPointer);
	fclose(dataPointer);
}

void Table::initCode()
{
	code = 0;
	FILE* dataPointer = fopen("tabledata.bin", "wb+");
	fwrite(&code, sizeof(uint32_t), 1, dataPointer);
	fclose(dataPointer);
}

void Table::saveData()
{
	saveCode();
	buffer.saveData();
}
