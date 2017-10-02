#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
	char name[30];
	int number;
} Person;

void correct(char *s) {
  for (int i=0; i<strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}


void readFile(FILE *fin, Person a[]) {
	char buff[100];
        int i = 0;
	while(fgets(buff,100,fin) != NULL) {
		sscanf(buff,"%s %d",a[i].name,&a[i].number);
		correct(a[i].name);
		i++;
	}
}


int cmpfunc (const void * a, const void * b)
{
	Person *c = (Person *)a;
	Person *d = (Person *)b;
   	return strcmp(c->name,d->name);
}


void print(Person a[], int size) {
	for (int i = 0; i < size; i++)
	{
		printf("%-20s%d\n", a[i].name,a[i].number);
	}
}


int main()
{	
	Person arr[15];
	FILE *fp = fopen("phonebook.txt","r");
	if (fp == NULL) return 1;
	readFile(fp,arr);
	qsort(arr, 15, sizeof(Person), cmpfunc);
	print(arr, 15);
	fclose(fp);
	return 0;
}
