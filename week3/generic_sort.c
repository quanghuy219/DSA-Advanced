#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void create_array(int* a, int size) { 
  srand(time(NULL));
  for (int i = 0; i < size; ++i)
  {
    a[i] = rand() % 10;
  }
}

int compare(const void* a, const void* b) {
	int m,n;
	m = *((int*)a);
	n = *((int*)b);
	return m - n;
}

void* my_memcpy(void* region1, const void* region2, size_t n) {
	const char* first = (const char*) region2;
	const char* last = ((const char*) region2) + n;
	char* result = (char*) region1;
	while(first != last) *result++ = *first++;
}

void exch(void* buff, int size, int i, int j) {
	void* tmp = malloc(size);
	memcpy(tmp, (char*)buff+i*size, size);
	memcpy((char*)buff+i*size, (char*)buff+j*size, size);
	memcpy((char*)buff+j*size, tmp, size);
	free(tmp);
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

void print(int a[], int size) {
  	for (int i = 0; i < size; i++)
  	{
    	printf("%d    ", a[i]);
  	}
  	printf("\n");
}

int main() {
	int size = 15;
  	int *a = (int*)malloc(size * sizeof(int));
	create_array(a,size);
	print(a,size);
	printf("\n");
	sort(a,sizeof(int),0,size-1,compare);
	print(a,size);
  	return 0;
}