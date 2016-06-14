#include "datafile.h"
#include "table.h"
#include "table_entry.h"
#include "datablock.h"
#include "rowid.h"
#include <fstream>
#include <iostream>
#include <string>

void print_arruda() {
	std::string line;
	std::ifstream myfile("data/arruda.txt");
	if (myfile) {
		while (getline(myfile, line)) {
			std::cout << line << std::endl;
		}
		myfile.close();
	}
	else
		std::cout << "fooey\n" << std::endl;
}


int main() {

	std::ifstream ifile("datafile.part");
	if (!ifile)
		Datafile::init();

	Table table;

	RowID rowid1 = table.newEntry("matthias gay");
	table.getEntry(RowID(0,0));

	table.saveData();

	return 0;
}
