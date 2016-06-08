#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <vector>
#include "datablock.h"
#include "table_entry.h"
#include "rowid.h"

class Buffer
{
public:
	Buffer();
	~Buffer();
	RowID newEntry(TableEntry entry);
	TableEntry getEntry(RowID rowID);

private:
	std::vector<DataBlock> datablocks;
};

#endif //BUFFER_H
