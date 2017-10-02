#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
	char name[30];
	int number;
} Person;


void print(Person a[], int size) {
	for (int i = 0; i < size; i++)
	{
		printf("%-20s%d\n", a[i].name,a[i].number);
	}
}

int cmpfunc (const void * a, const void * b)
{
	Person *c = (Person *)a;
	Person *d = (Person *)b;
   	return strcmp(c->name,d->name);
}


int main()
{	
	FILE *f2 = fopen("phone.dat","rb");
	fseek(f2, 0 ,SEEK_END);
	int size = ftell(f2) / sizeof(Person);
	fseek(f2,0,SEEK_SET);
	
	Person *a = (Person*)malloc(size * sizeof(Person));

	fread(a, sizeof(Person), size, f2);
	qsort(a, size, sizeof(Person), cmpfunc);
	print(a,size);
	fclose(f2);
	return 0;
}