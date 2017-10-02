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

Entry makeNode(void* name, void* number) {
  Entry  newEntry;
  newEntry.key = strdup((char*)name);
  newEntry.value = malloc(sizeof(long));
  memcpy(newEntry.value, number, sizeof(long));
  return newEntry;
}

int compare(void* a, void* b) {
  return strcmp( (char*)a, (char*)b );
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

void print(SymbolTable phoneBook){
  printf("%-20s%s\n","Name","Number");
  for(int i = 0; i < phoneBook.total; i++) {
    printf("%-20s%ld\n",(char*)phoneBook.entries[i].key, *(long*)phoneBook.entries[i].value);
  }
  printf("Total: %d\n",phoneBook.total);
}

int main()
{
  SymbolTable phoneBook = createTable(makeNode, compare);
  phoneBook.entries = (Entry*)malloc(INCREMENT_SIZE);
  phoneBook.size = INCREMENT_SIZE;

  char *name = (char*)malloc(MAX * sizeof(char));

  long number;
  int choice;
  while(1) {
    printf("Enter: \n");
    printf("1. Add new entry\n");
    printf("2. Get entry by name\n");
    printf("3. Drop table and quit\n");
    scanf("%d%*c",&choice);
    
    switch(choice) {
    case 1:
      name[0] = '\0';
      while( strlen(name) == 0) {    
	printf("Name:  ");
	fgets(name,30,stdin);
	if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
      }
      printf("Number:   ");
      scanf("%ld",&number);

      addEntry(name,&number,&phoneBook);
      
     printf("\n\n");
     print(phoneBook);
     break;

    case 2:
      printf("Name:  ");
      fgets(name,MAX,stdin);
      if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
      Entry *result = getEntry(name,phoneBook);
      if (result != NULL) {
	printf("\n%-20s%ld\n",(char*)result->key,*(long*)result->value);
      } else printf("\nNot found\n");
      break;

    case 3:
      printf("Quit\n");
      dropTable(&phoneBook);
      return 0;

    default:
      printf("Invalid input");
      break;
    }
    printf("\n\n");
  }

  
  return 0;
}
