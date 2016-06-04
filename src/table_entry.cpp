#include "table_entry.h"
#include <cstdint>
#include <string>

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

