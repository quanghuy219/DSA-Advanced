#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100
#define INCREMENT_SIZE 10
#define MAX 30

typedef struct {
  void *key;
  void *value;
} Entry;

typedef struct {
  Entry *entries;
  int size, total;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*,void*);
} SymbolTable;

Entry makeNode(void* key, void* value) {
  Entry  newEntry;
  newEntry.key = strdup((char*)key);
  newEntry.value = malloc(sizeof(long));
  memcpy(newEntry.value, value, sizeof(long));
  return newEntry;
}

SymbolTable createTable(Entry(*makeNode)(void*,void*), int (*compare)(void*,void*)) {
  SymbolTable new;
  new.makeNode = makeNode;
  new.compare = compare;
  return new;
}

void addEntry(SymbolTable *table, void* key, void* value) {
  Entry new = makeNode(key,value);
  while(table->size < (table->total +1) * sizeof(Entry) ) {
    table->entries = realloc(table->entries, table->size + INCREMENT_SIZE );
    table->size += INCREMENT_SIZE;
  }
  table->entries[table->total++] = new;
}

Entry* getEntry(SymbolTable table, void* key) {
  for(int i = 0; i < table.total; i++) {
    if ( table.compare( key, table.entries[i].key  ) == 0) {
      return &table.entries[i];
    }
  }
  return NULL;
}

void dropTable(SymbolTable *tab) {
  for(int i = 0; i < tab->total; i++) {   
    free(tab->entries[i].key);
    free(tab->entries[i].value);
  }
  free(tab->entries);
}
