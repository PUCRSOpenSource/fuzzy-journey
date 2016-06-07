#ifndef TABLE_ENTRY_H
#define TABLE_ENTRY_H

#include <cstdint>
#include <string>
#include <cstring>

class TableEntry
{
	public:
		TableEntry(uint32_t code, std::string description);
		TableEntry(uint8_t *byteArray, uint16_t size);
		~TableEntry();
		uint32_t getCode();
		std::string getDescription();
		uint32_t size();
		uint8_t *toByteArray();
	private:
		uint32_t code;
		std::string description;
};

#endif /* TABLE_ENTRY_H */
