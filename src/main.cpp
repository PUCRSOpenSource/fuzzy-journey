#include "datafile.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void print_arruda()
{
	string line;
	ifstream myfile("data/arruda.txt");
	if (myfile)  // same as: if (myfile.good())
	{
		while (getline( myfile, line ))  // same as: while (getline( myfile, line ).good())
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "fooey\n";
}


int main()
{
	print_arruda();
	return Datafile::init();
}
