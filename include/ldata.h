#ifndef LDATA_H
#define LDATA_H

#include <cstdint>
#include "rowid.h"

class LData
{
	public:
		LData(uint32_t index, RowID rowID);
		~LData();
		uint32_t getIndex();
		RowID getRowID();
		void setRowID(RowID rowID);
	private:
		uint32_t index;
		RowID rowID;
};

#endif //LDATA_H
