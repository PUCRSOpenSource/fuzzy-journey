#include "datafile.h"
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
	TableEntry* te = new TableEntry(1, "blabla");
	std::cout << "Code: " << te->getCode() << std::endl;
	std::cout << "Description: " << te->getDescription() << std::endl;
}
