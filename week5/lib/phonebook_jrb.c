#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"

void correct(char *s) {
  for (int i = 0; i < strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}

void add(JRB tree, char* key, long val) {
	JRB node = jrb_find_str(tree, key);
	if(node == NULL) jrb_insert_str(tree, strdup(key), new_jval_l(val));
	else {
		printf("\nRecord exists\n\n");
	}
}

void delete(JRB tree, char* key) {
  JRB node = jrb_find_str(tree,key);
	if (node == NULL) printf("Not found\n");
	else jrb_delete_node(node);
}

void modify(JRB tree, char* key, long new_number) {
	JRB node = jrb_find_str(tree, key);
	if (node == NULL) printf("Not found\n");
	else {
		node->val = new_jval_l(new_number);
	}
}

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

void menu1(JRB tree) {
	char* name = (char*)malloc(30 * sizeof(char));
	long number;

	printf("Add new record\n");
	printf("Name: ");
	fgets(name, 30, stdin);
	if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
	printf("Number: ");
	scanf("%ld%*c",&number);
	add(tree, name, number);
	free(name);
}

void menu2(JRB tree) {
	char* name = (char*)malloc(30 * sizeof(char));
	printf("Delete\n");
	printf("Name: ");
	fgets(name,30,stdin);
	if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
	delete(tree,name);
	free(name);
}

void menu3(JRB tree) {
	char* name = (char*)malloc(30 * sizeof(char));
	long number;
	printf("Edit record\n");
	printf("Name: ");
	fgets(name, 30, stdin);
	if(name[strlen(name) -1] == '\n') name[strlen(name) - 1] = '\0';
	printf("Number: ");
	scanf("%ld%*c",&number);
	modify(tree, name, number);
	free(name);
}

int main()
{
	JRB book = make_jrb();
	JRB node;
	FILE *f1 = fopen("phonebook.txt","r");
	readFile(f1, book);
	jrb_traverse(node, book) {
		printf("%-30s %ld\n",  jval_s(node->key), jval_l(node->val)  );
	}
	printf("\n\n\n");

	int choice;

	while(1) {
		printf("1. Add record\n");
		printf("2. Delete record\n");
		printf("3. Edit record\n");
		printf("0. Quit\n");
		scanf("%d",&choice);
		while(getchar() != '\n');
		switch(choice) {
			case 1: menu1(book);
				break;
			case 2: menu2(book);
				break;
			case 3: menu3(book);
				break;
			case 0: 
				jrb_free_tree(book);
				return 0;
		}
		jrb_traverse(node, book) {
			printf("%-30s %ld\n",  jval_s(node->key), jval_l(node->val)  );
		}
		printf("\n\n\n");
	}
	fclose(f1);
	return 0;
}
