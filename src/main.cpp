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

	//RowID rowid1 = table.newEntry("Oi td bem amg");
	RowID rowid1(0,0);
	//RowID rowid2 = table.newEntry("Oi td amg e vom vc");
	table.getEntry(rowid1);
	//table.getEntry(rowid2);
	//table.remove(rowid1);
	//table.remove(rowid2);
	//table.getEntry(rowid1);
	//table.getEntry(rowid2);
	//RowID rowid3 = table.newEntry("Essa 'e uma nov entry bem loca");
	//table.getEntry(rowid3);
	//RowID rowid4 = table.update(rowid3, "oh noes, fui updateado");
	//table.getEntry(rowid3);
	//table.getEntry(rowid4);

	return 0;
}
