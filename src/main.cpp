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

	try {
		table->newEntry(0, "Ta saindo da jaula o monstro porra!");
	}
	catch( const std::runtime_error& ex ) {
		std::cerr << ex.what() << std::endl;
	}

	try {
		table->newEntry(0, "Ta entrando na jaula o monstro porra!");
	}
	catch( const std::runtime_error& ex ) {
		std::cerr << ex.what() << std::endl;
	}

	try {
		TableEntry entry = table->getEntry(0);
		std::cout << entry.getDescription() << std::endl;
	}
	catch( const std::runtime_error& ex ) {
		std::cerr << ex.what() << std::endl;
	}

	try {
		TableEntry entry = table->getEntry(50);
		std::cout << entry.getDescription() << std::endl;
	}
	catch( const std::runtime_error& ex ) {
		std::cerr << ex.what() << std::endl;
	}



	return 0;
}
