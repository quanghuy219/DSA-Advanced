#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

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

char* convertName(char *s) {
	if(s == NULL) return NULL;

	char *token;
	char s1[MAX];
	strcpy(s1,s);
	token = strtok(s1," ");
	char tmp[MAX][MAX];
	int count = 0;
	char *result = (char*)malloc(sizeof(char) * MAX);

	while(token != NULL) {
		strcpy(tmp[count++], token);
		token = strtok(NULL," ");
	}
	for (int i = count-1; i >= 0; i--)
	{
		strcat(result,tmp[i]);
		strcat(result," ");
	}

	while (!isalpha(result[strlen(result) - 1]))
	{
		result[strlen(result) - 1] = '\0';
	}
	return result;
}

int cmpfunc (const void * a, const void * b)
{	
	Person *c = (Person *)a;
	Person *d = (Person *)b;
   	return strcmp(convertName(c->name),convertName(d->name));
}

void exch(void* buff, int size, int i, int j) {
	void* tmp = malloc(size);
	memcpy(tmp, (char*)buff+i*size, size);
	memcpy((char*)buff+i*size, (char*)buff+j*size, size);
	memcpy((char*)buff+j*size, tmp, size);
}

void sort(void *a, int size, int l, int r, int (*compare)(const void*,const void*)) {
  	if(r<=l) return;
  	int i=l-1,j=r;
  	int p=l-1,q=r;
  	while(1)
    {
	    while( compare( (char*)a+(++i)*size , (char*)a+r*size ) < 0 );
	    while( compare( (char*)a+r*size , (char*)a+(--j)*size ) < 0 ) if(j==l) break;
	    if(i>=j) break;
	    exch(a,size,i,j);
	    if(compare( (char*)a+(i)*size , (char*)a+r*size ) == 0) exch(a, size, ++p, i);
	    if(compare( (char*)a+(j)*size , (char*)a+r*size ) == 0) exch(a, size, --q, j);
    }
  	exch(a, size, i, r);
  	j=i-1;
  	i=i+1;
  	for(int k=l;k<=p;k++) exch(a, size, k, j--);
  	for(int k=r-1;k>=q;k--) exch(a, size, k, i++);
  	sort(a, size, l, j, compare);
  	sort(a, size, i, r, compare);
}


int main()
{	
	FILE *f2 = fopen("phone.dat","rb");
	fseek(f2, 0,SEEK_END);
	int total = ftell(f2) / sizeof(Person);
	fseek(f2, 0, SEEK_SET);
	
	Person *a = (Person*)malloc(total * sizeof(Person));

	fread(a, sizeof(Person), total, f2);

	sort(a, sizeof(Person), 0, total-1, cmpfunc);
	print(a,total);
	fclose(f2);
	return 0;
}