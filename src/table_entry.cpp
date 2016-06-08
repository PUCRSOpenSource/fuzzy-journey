#include "table_entry.h"
#include <iostream>

TableEntry::TableEntry(uint32_t code, std::string description)
{
	this->code        = code;
	this->description = description;
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
	for (size_t i = 0; i < description.size(); i++) {
		array[sizeof(code) + i] = description[i];
	}
	return array;
}
