#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <cstdlib>
#include <vector>
#include "datablock.h"
#include "table_entry.h"
#include "rowid.h"

#define DATABLOCK_SIZE 2000

class Buffer
{
public:
	Buffer();
	~Buffer();
	RowID newEntry(TableEntry entry);
	TableEntry getEntry(RowID rowID);
	void remove(RowID rowID);
	void loadDatablock(int16_t index);
	void saveDatablock(DataBlock datablock);
	void saveData();

private:
	std::vector<DataBlock> datablocks;
};

#endif //BUFFER_H
