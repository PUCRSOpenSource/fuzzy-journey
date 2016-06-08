#ifndef ROWID_H
#define ROWID_H

#include <cstdint>

class RowID
{
public:
	RowID(int32_t blockNumber, int32_t position);
	~RowID();
	int32_t getBlockNumber();
	int32_t getPosition();
private:
	int32_t blockNumber;
	int32_t position;
};

#endif //ROWID_H
