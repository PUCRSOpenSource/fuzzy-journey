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

TableEntry Table::getEntry(RowID rowID)
{
	TableEntry entry = buffer.getEntry(rowID);
	std::cout <<
	"Now I would get an entry with code: " <<
	entry.getCode() <<
	" - and description: " <<
	entry.getDescription() <<
	std::endl;
	return entry;
}

void Table::remove(RowID rowID)
{
	TableEntry entry = buffer.getEntry(rowID);
	std::cout <<
	"Now I will remove an entry with code: " <<
	entry.getCode() <<
	" - and description: " <<
	entry.getDescription() <<
	std::endl;
	buffer.remove(rowID);
}

RowID Table::update(RowID rowID, std::string description)
{

	TableEntry entry = getEntry(rowID);

	std::cout <<
	"Now I will update an entry with code: " <<
	entry.getCode() <<
	" - and description: " <<
	entry.getDescription() <<
	std::endl;

	remove(rowID);
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
