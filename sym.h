/*This program serves as the public API for both modules*/
#ifndef SYM_H_INCLUDED
#define SYM_H_INCLUDED

#include <stddef.h> /*for size t*/

 SymTable_T SymTable_new(void);

  void SymTable_free(SymTable_T oSymTable);

  size_t SymTable_getLength(SymTable_T oSymTable);

  int SymTable_put(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);

  void *SymTable_replace(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);

  int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

  void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

  void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

  void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra);
     
#endif /* SYM_H_INCLUDED */