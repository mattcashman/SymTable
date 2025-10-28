/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive. */
   #include <assert.h>
   #include "SymTablehash.h"
   #include <stddef.h>
   #include <string.h>

   #define NUM_BUCKETS 509

struct Binding {
   const char *pcKey;
   const void *pvValue;
   struct Binding *psNextBinding;
};

struct SymTable {
    struct Binding **ppsBuckets;
    size_t uBucketCount;
    size_t numBuckets;
}; 

static size_t SymTable_hash(const char *pcKey, size_t uBucketCount) {
   const size_t HASH_MULTIPLIER = 65599;
   size_t u;
   size_t uHash = 0;

   assert(pcKey != NULL);

   for (u = 0; pcKey[u] != '\0'; u++)
      uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

   return uHash % uBucketCount;
}

SymTable_T SymTable_new(void) {
   symtable_T oSymTable;
   size_t i;

   oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

   oSymTable->uBucketCount = INITIAL_NUM_BUCKETS;
   oSymTable->uBindingCount = 0;
   
   oSymTable->ppsBuckets = (struct Binding **)malloc(
      oSymTable->uBucketCount * sizeof(struct Binding *));

   if (oSymTable->ppsBuckets == NULL) {
      free(oSymTable);
      return NULL;
   }
   for (i = 0; i < oSymTable->uBucketCount; i++)
      oSymTable->ppsBuckets[i] = NULL;
   
   return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {

   size_t i;
   struct Binding *psCurrent;
   struct Binding *psNext;

   assert(oSymTable != NULL);

   for (i=0; oSymTable-> uBucketCount; i++) {
      psCurrent = oSymTable->ppsBuckets[i];

      while (psCurrent != NULL) {
         psNext = psCurrent->psNextBinding;
         free((void*)psCurrent->pcKey);
         free(psCurrent);
         psCurrent = psNext;
      }
   }
   free(oSymTable->ppsbuckets);
   free(oSymTable);
}

size_t SymTable_getlength(SymTable_T oSymTable) {
    
    assert(oSymTable != NULL);
    return oSymTable->uBindingCount;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {

   size_t index; 
   struct Binding *psCurrent;
   struct Binding *psNewBinding;
   char *pcKeyCopy;

   assert(oSymTable != NULL);
   assert(pcKey != NULL)

   Index = SymTable_hash(pcKey, oSymTable -> uBucketCount);

   for (psCurrent = oSymTable->ppsBuckets[index]; psCurrent != NULL; 
      psCurrent = psCurrent->psNextBinding) {
      if (strcmp(psCurrent->pckey, pcKey) == 0) {
         return 0; // Key already exists
      }
   }

   psNewBinding = (struct Binding *)malloc(sizeof(struct Binding));
   if (psNewBinding == NULL) {
      return 0; // Memory allocation failed
   }

   pcKeyCopy = (char *)malloc(strlen(pcKey) + 1);
   if (pcKeyCopy == NULL) {
      free(psNewBinding);
      return 0; // Memory allocation failed
   }
   
   strcpy(pcKeyCopy, pcKey);

   psNewBinding->pcKey = pcKeyCopy;
   psNewBinding->pcValue = pvValue;   
   psNewBinding->psNextBinding = oSymTable->ppsbuckets[index];
   oSymTable->ppsbuckets[index] = psNewBinding;

   oSymTable->uBindingCount++;

   return 1:
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue);{
    
   size_t index;
   Struct Binding *psCurrent;
   void *pvOldValue;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

   index = SymTable_hash(pcKey, oSymTable->uBucketCount);

    for (psCurrent = oSymTable->Top; psCurrent != NULL; psCurrent = psCurrent->Next) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            pvOldValue = (void*)psCurrent->value;
            psCurrent->value = pvValue;
            return pvOldValue;
        }
    }
    return NULL; 
}  

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);{

    size_t index;
    struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    index = SymTable_hash(pcKey, oSymTable->uBucketCount);

    for (psCurrent = oSymTable->ppsBuckets[index]; psCurrent != NULL; 
      psCurrent = psCurrent-> psNextBinding) {
        if (strcmp(psCurrent->key, pcKey) == 0) {
            return 1; // Key found
        }
    }

    return 0; // Key not found

}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);{
    
    size_t index;
    struct Binding *psCurrent;
    struct Binding *psPrevious = NULL;
    void *pvValue;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    index = SymTable_hash(pcKey, oSymTable->uBucketCount);
    psCurrent = oSymTable->ppsBuckets[index];

    while (psCurrent != NULL) {
        if (strcmp(psCurrent->pcKey, pcKey) == 0) {
            pvValue = (void*)psCurrent->pvValue;
          
            if (psPrevious == NULL) {
                oSymTable->ppsBuckets[index] = psCurrent->psNextBinding;
            } 
            else {
                psPrevious->psNextBinding = psCurrent->psNextBinding;
            }
            free((void*)psCurrent->pcKey);
            free(psCurrent);
            oSymTable->uBindingCount--;
            return pvValue;
        }
        psPrevious = psCurrent;
        psCurrent = psCurrent->psNextBinding;
    }
      return NULL;
}

void *SymTable_remove(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                  const void *pvExtra);{
    
    size_t i;
    struct Binding *psCurrent;

    assert(oSymTable != NULL);
    assert(pfApply != NULL);

    for (i = 0; i < oSymTable->uBucketCount; i++) {
        for (psCurrent = oSymTable->ppsBuckets[i]; psCurrent != NULL; 
           psCurrent = psCurrent->psNextBinding) {
            (*pfApply)(psCurrent->pcKey, (void*)psCurrent->pvValue, (void*)pvExtra);
        }
    }
}


