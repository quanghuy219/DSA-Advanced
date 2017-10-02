
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
void addEntry(void* key, void* value, SymbolTable *book);
Entry* getEntry(void* key, SymbolTable book);
void dropTable(SymbolTable *tab);
