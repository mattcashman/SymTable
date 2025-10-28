#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

struct Binding {
   char *key;
   const void *value;
   struct StackNode *Next;
};

struct SymTable {
    struct Binding *Top;
    sizeof_t length;
}; 

SymTable_T SymTable_new {
    struct Binding *Top;
    sizeof_t length;

   SymTable_T oSymTable;

   oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

   oSymTable->Top = NULL;
   oSymTable->length = 0;
   return oSymTable;
}

void SymTable_free(SymTable_T oSymTable)
{
   struct Binding *psCurrent;
   struct Binding *psNext;
   
   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode; psCurrentNode != NULL;
     psCurrentNode = psNextNode) {

      psNext = psCurrentNode->Next;
      free(psCurrentNode->key);
      free(psCurrentNode);
   }

   free(oSymTable);
}
size_int SymTable_getlength(SymTable_T oSymTable) {
    struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    
    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            return psCurrent->value;
        }
    }

    return NULL;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    
    Struct Binding *newBinding;
    Struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            return 0; // Key already exists
        }
    }

    pcNewKey = malloc(sizeof(PcKey) + 1);
    if (pcNewKey == NULL) {
        return 0; // Memory allocation failed
    }
    strcpy(pcNewKey, pcKey);

    psNewBinding = malloc(sizeof(struct Binding));
    if (psNewBinding == NULL) {
        free(pcNewKey);
        return 0; // Memory allocation failed   
    }

    psNewBinding->key = pcNewKey;
    psNewBinding->value = pvValue;
    psNewBinding->Next = oSymTable->Top;

    oSymTable->Top = psNewBinding;
    oSymTable->length++;
    return 1; // Success
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue);{
    Struct Binding *psCurrent;
    Struct Binding *psPrevious = NULL;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            if(psPrevious == NULL) {
                oSymTable->Top = psCurrent->Next;
            } 
            else {
                psPrevious->Next = psCurrent->Next;
            }
            free(psCurrent->key);
            free(psCurrent);
            oSymTable->length--;
            return 1;
        }
        psPrevious = psCurrent;
    }
    
    return 0; 
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            return 1; // Key found
        }
    }

    return 0; // Key not found

}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);{
    struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            return (void*)psCurrent->value; // Key found
        }
    }

    return NULL; // Key not found

}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);{
    struct Binding *psCurrent;
    struct Binding *psPrevious = NULL;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            if (psPrevious == NULL) {
                oSymTable->Top = psCurrent->Next;
            } else {
                psPrevious->Next = psCurrent->Next;
            }
            void *pvValue = (void*)psCurrent->value;
            free(psCurrent->key);
            free(psCurrent);
            oSymTable->length--;
            return pvValue; // Return the removed value
        }
        psPrevious = psCurrent;
    }

    return NULL; // Key not found

}

void SymTable_map(Stack_T oStack, void (*pfApply)(void *pvItem, void *pvExtra),
               const void *pvExtra)
{
   struct SymTableNode *psCurrentNode;

   assert(oSymTable != NULL);
   assert(pfApply != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
      (*pfApply)((void*)psCurrentNode->pvItem, (void*)pvExtra);
}