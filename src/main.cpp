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

	Table table;

	RowID rowid1 = table.newEntry("matthias gay");

	table.saveData();

	Branch b;
	Leaf l;
	b.insert(32, rowid1);
	l.insert(32, rowid1);

	BTree btree(new Leaf());

	for (int i = 0; i < 20; i++) {
		std::cout << "=========" << std::endl;
		std::cout << "=========" << std::endl;
		std::cout << "Insert " << i <<  std::endl;
		std::cout << "---------" << std::endl;
		btree.insert(i, rowid1);
		btree.print();
		std::cout << "=========" << std::endl;
	}

	return 0;
}
