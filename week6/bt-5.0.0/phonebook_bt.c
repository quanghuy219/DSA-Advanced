#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"


void correct(char *s) {
  for (int i = 0; i < strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}

/*
void readFile(FILE *f1, JRB tree) {
  char buff[100];
  char *name = (char*)malloc(30 * sizeof(char));	
  long number;
	while(fgets(buff,100,f1) != NULL) {
		sscanf(buff, "%s %ld", name, &number);
		correct(name);
		jrb_insert_str(tree, strdup(name), new_jval_l(number));
	}
	free(name);
}
*/

int main()
{
  btinit();
  BTA *book = btcrt("phonebook.txt", 1, 0);
  if (book == NULL) return 0;

  char* name = (char*)malloc(30);
  char* number = (char*)malloc(20);

  fgets(name,30,stdin);
  if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
  fgets(number,20,stdin);
  if(number[strlen(number) -1] == '\n') number[strlen(number) - 1] = '\0';

  btins(book,name,number,20);
  return 0;
}




