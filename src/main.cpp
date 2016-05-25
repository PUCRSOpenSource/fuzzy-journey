#include "datafile.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void print_arruda()
{
	string line;
	ifstream myfile("data/arruda.txt");
	if (myfile)
	{
		while (getline( myfile, line ))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "fooey\n" << endl;
}


int main()
{
	print_arruda();
	return Datafile::init();
}
