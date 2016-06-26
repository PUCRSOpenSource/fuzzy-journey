#ifndef TABLE_H
#define TABLE_H

#include "table_entry.h"
#include "buffer.h"
#include "rowid.h"
#include "btree.h"
#include "ldata.h"
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>

#ifdef __cplusplus

class Table
{
	public:
		~Table();
		RowID insert(uint32_t code, std::string description);
		TableEntry select(uint32_t code);
		void remove(uint32_t code);
		void update(uint32_t code, std::string description);
		void printBTree();
		void loadBTreeData();
		void saveData();
		static Table* getInstance();

	private:
		Table();
		Buffer buffer;
		BTree* btree;
		static Table* t_Instance;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif
void* getTable();
void printTableTree(void* table);
#ifdef __cplusplus
}
#endif

#endif /* TABLE_H */
