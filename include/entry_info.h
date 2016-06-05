//
// Created by Daniel Amarante on 6/5/16.
//

#ifndef ENTRY_INFO_H
#define ENTRY_INFO_H

#include <cstdint>

class EntryInfo
{
public:
	EntryInfo(uint16_t position, uint16_t size);
	~EntryInfo();
private:
	uint16_t position;
	uint16_t size;
};

#endif //ENTRY_INFO_H
