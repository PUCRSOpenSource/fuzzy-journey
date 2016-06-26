#include "datafile.h"
#include "table.h"
#include "table_entry.h"
#include "datablock.h"
#include "rowid.h"
#include "leaf.h"
#include "branch.h"
#include "btree.h"
#include <fstream>
#include <iostream>
#include <string>

void print_arruda()
{
	std::string line;
	std::ifstream myfile("data/arruda.txt");
	if (myfile)
	{
		while (getline(myfile, line))
		{
			std::cout << line << std::endl;
		}
		myfile.close();
	}
	else
		std::cout << "fooey\n" << std::endl;
}

int main()
{

	std::ifstream ifile("datafile.part");
	if (!ifile)
		Datafile::init();

	Table* table = Table::getInstance();

//	table->insert(200, "Ta saindo da jaula o monstro porra");
//	TableEntry entry = table->select(200);
//	std::cout << "selecting element " << entry.getCode() << " - " << entry.getDescription() << std::endl;
//
//	table->update(200, "Ja saiu da jaula o monstro porra");
//	entry = table->select(200);
//	std::cout << "selecting element " << entry.getCode() << " - " << entry.getDescription() << std::endl;

	int max = 5;

	for (int i = 0; i < max; i++) {
		std::cout << "=========" << std::endl;
		std::cout << "Insert " << i <<  std::endl;
		std::cout << "---------" << std::endl;
		table->insert(i, "Ta saindo da jaula o monstro porra");
		table->printBTree();
		std::cout << "=========" << std::endl;
	}

	for (int i = 0; i < max; i++) {
		std::cout << "=========" << std::endl;
		std::cout << "Select " << i <<  std::endl;
		std::cout << "---------" << std::endl;
		TableEntry entry = table->select(i);
		std::cout << "selecting element " << entry.getCode() << " - " << entry.getDescription() << std::endl;
		std::cout << "=========" << std::endl;
	}

	table->saveData();

	return 0;
}
