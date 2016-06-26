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
	
	BTree* btree = new BTree(new Leaf());
	Table* table = new Table(btree);

	table->newEntry("Ta saindo da jaula o monstro porra!");

	try {
		TableEntry entry = table->getEntry(50);
		std::cout << entry.getDescription() << std::endl;
	}
	catch( const std::runtime_error& e ) {
		std::cout << "Your code was not found" << std::endl;
	}

	return 0;
}
