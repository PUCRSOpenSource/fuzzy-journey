#ifndef ROWID_H
#define ROWID_H

#include <cstdint>

class RowID
{
public:
	RowID(int16_t blockNumber, int16_t position);
	~RowID();
	int16_t getBlockNumber();
	int16_t getPosition();
private:
	int16_t blockNumber;
	int16_t position;
};

#endif //ROWID_H
