#include "table_entry.h"
#include <stdlib.h>
#include <iostream>

TableEntry::TableEntry(uint32_t code, std::string description)
{
	this->code        = code;
	this->description = description;
}

TableEntry::TableEntry(uint8_t *byteArray, uint16_t size)
{
	memcpy(&code, byteArray, sizeof(code));
	memcpy(&description, byteArray + sizeof(code), size - sizeof(code));
	free(byteArray);
}

TableEntry::~TableEntry()
{

}

uint32_t TableEntry::getCode()
{
	return code;
}

std::string TableEntry::getDescription()
{
	return description;
}

uint32_t TableEntry::size()
{
	return sizeof(code) + description.size();
}

uint8_t *TableEntry::toByteArray()
{
	uint8_t *array = static_cast<uint8_t *>(malloc(size()));
	memcpy(array, &code, sizeof(code));
	memcpy(array + sizeof(code), &description, description.size());
	return array;
}
