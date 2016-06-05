#include "datafile.h"
#include "table.h"
#include "table_entry.h"
#include "datablock.h"
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
	TableEntry te(1, "Oi td bem");
	DataBlock *db = new DataBlock(123);
	db->addEntry(te);

	return 0;
}
