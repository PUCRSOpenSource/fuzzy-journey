#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void* getTable();
void printTableTree(void* table);
void insertTable(void* table, uint32_t code, char* description);
void insertNTable(void* table, uint32_t n);
void updateTable(void* table, uint32_t code, char* description);
void selectTable(void* table, uint32_t code);
void selectDTable(void* table, char* description);
void saveTableData(void* table);
#ifdef __cplusplus
}
#endif
