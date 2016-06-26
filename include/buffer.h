#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <deque>
#include "datablock.h"
#include "table_entry.h"
#include "ldata.h"
#include "rowid.h"

#define DATABLOCK_SIZE 2000
#define FRAMES 2
#define DATABLOCKS_TOTAL 16384

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
		int16_t chooseDatablock();
		bool isLoaded(uint16_t index);
		std::vector<LData> allEntries();
		DataBlock getDatablockReadOnly(int16_t index);

	private:
		std::deque<DataBlock> datablocks;
		uint16_t loadingIterator;
};

#endif //BUFFER_H
