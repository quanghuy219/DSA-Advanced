#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

#define INITIAL_SIZE 100
#define INCREMENT_SIZE 10
#define MAX 30

Entry makeNode(void* name, void* number) {
  Entry  newEntry;
  newEntry.key = strdup((char*)name);
  newEntry.value = malloc(sizeof(long));
  memcpy(newEntry.value, number, sizeof(long));
  return newEntry;
}

SymbolTable createTable(Entry(*makeNode)(void*,void*), int (*compare)(void*,void*)) {
  SymbolTable new;
  new.makeNode = makeNode;
  new.compare = compare;
  return new;
}

void addEntry(void* key, void* value, SymbolTable *book) {
  Entry new = makeNode(key,value);
  while(book->size < (book->total +1) * sizeof(Entry) ) {
    book->entries = realloc(book->entries, book->size + INCREMENT_SIZE );
    book->size += INCREMENT_SIZE;
  }
  book->entries[book->total++] = new;
}

Entry* getEntry(void* key, SymbolTable book) {
  for(int i = 0; i < book.total; i++) {
    if ( book.compare( key, book.entries[i].key  ) == 0) {
      return &book.entries[i];
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
