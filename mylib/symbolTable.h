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

Entry makeNode(void* name,void* number);
SymbolTable createTable(Entry(*makeNode)(void*,void*), int (*compare)(void*,void*));
void addEntry(SymbolTable *table, void* key, void* value);
Entry* getEntry(SymbolTable table, void* key);
void dropTable(SymbolTable *table);
