#include "datafile.h"
#include "table.h"
#include "table_entry.h"
#include <fstream>
#include <iostream>
#include <string>

void print_arruda()
{
	std::string line;
	std::ifstream myfile("data/arruda.txt");
	if (myfile)
	{
		while (getline( myfile, line ))
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
	print_arruda();
	Datafile::init();
	Table t;
	t.newEntry("blabla");
	t.newEntry("blablabla");
	t.printMembers(); // For DEBUG.
	std::cout << "Table class size: " << sizeof(class TableEntry) << std::endl;
}
