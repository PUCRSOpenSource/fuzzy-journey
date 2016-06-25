#include "datablock.h"
#include <iostream>
#include <string>
#include <cstring>

// TODO: Initialize datablock receiving data from parameter with data read from file.
// TODO: Change add entry to be able to write in deleted spaces. (low priority)

DataBlock::DataBlock(uint16_t address)
{
	// This initialization is not final remove when fetch from file is done.
	this->address = address;
	for (int i = 0; i < SIZE; i++)
	{
		data[i] = 0;
	}
	headerSize = 0;
}

DataBlock::DataBlock(uint16_t address, int headerSize, uint8_t data[SIZE])
{
	this->address = address;
	this->headerSize = headerSize;
	memcpy(this->data, data, SIZE);
}

DataBlock::~DataBlock()
{

}

int16_t DataBlock::getAddress()
{
	return address;
}


int16_t DataBlock::addEntry(TableEntry entry)
{
	uint16_t lastPosition = lastHeaderPosition();;
	uint16_t lastSize = lastHeaderSize();
	uint16_t position = lastPosition + lastSize;

	int16_t actualPosition = SIZE - position - entry.size();

	if (actualPosition <= headerSize + 4)
	{
		return -1;
	}

	saveNewHeader(position, entry.size());
	saveNewEntry(actualPosition, entry);

	return headerSize / 4 - 1;
}

uint16_t DataBlock::lastHeaderPosition()
{
	if (headerSize <= 0)
	{
		return 0;
	}
	uint16_t position;
	memcpy(&position, data + headerSize - 4, sizeof(position));
	return position;
}

uint16_t DataBlock::lastHeaderSize()
{
	if (headerSize <= 0)
	{
		return 0;
	}
	uint16_t size;
	memcpy(&size, data + headerSize - 2, sizeof(size));
	return size;
}

void DataBlock::saveNewHeader(uint16_t position, uint16_t size)
{
	memcpy(data + headerSize, &position, sizeof(uint16_t));
	memcpy(data + headerSize + 2, &size, sizeof(uint16_t));
	headerSize += 4;
}

void DataBlock::saveNewEntry(uint16_t position, TableEntry entry)
{
	uint8_t *entryData = entry.toByteArray();
	memcpy(data + position, entryData, entry.size());
	free(entryData);
}

TableEntry DataBlock::getEntry(int16_t index)
{
	uint32_t entryCode;
	std::string entryDescription;

	int16_t position = getHeaderPosition(index);
	int16_t size = getHeaderSize(index);

	if (position == -1)
	{
		return TableEntry(666, "error!! error!!! thiw was deleted !!!");
	}

	int16_t actualPosition = SIZE - position - size;

	memcpy(&entryCode, data + actualPosition, sizeof(entryCode));

	for (uint16_t i = 0; i < size - 4; i++)
	{
		uint8_t character = data[actualPosition + 4 + i] & 0xFF;
		entryDescription.push_back(character);
	}

	return TableEntry(entryCode, entryDescription);
}

uint16_t DataBlock::getHeaderPosition(uint16_t index)
{
	uint16_t position;
	memcpy(&position, data + 4 * index, sizeof(position));
	return position;
}

uint16_t DataBlock::getHeaderSize(uint16_t index)
{
	uint16_t size;
	memcpy(&size, data + 4 * index + 2, sizeof(size));
	return size;
}

void DataBlock::remove(int16_t index)
{
	int16_t position = -1;
	memcpy(data + 4 * index, &position, sizeof(uint16_t));
}

int DataBlock::getHeaderSize()
{
	return headerSize;
}

uint8_t* DataBlock::getData()
{
	return data;
}
