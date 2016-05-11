#include <cstdio>
#include <cstdint>
#include "datafile.h"

int Datafile::init()
{
	uint8_t data = 0x00;
	FILE* ptr_mydatafile;
	ptr_mydatafile = fopen("datafile.part", "wb");
	for (int i = 0; i < 32 * MB; i++)
		fwrite(&data, sizeof(data), 1, ptr_mydatafile);
	fclose(ptr_mydatafile);
	return 0;
}
