#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jval.h"

int compare_i(Jval* a, Jval* b) {
  return a->i - b->i;
}

int compare_f(Jval* a, Jval* b) {
  return a->f - b->f;
}

int compare_d(Jval* a, Jval* b) {
  return a->d - b->d;
}

int compare_l(Jval* a, Jval* b) {
  return a->l - b->l;
}

int compare_c(Jval* a, Jval* b) {
  return a->c - b->c;
}

int compare_s(Jval* a, Jval* b) {
  return strcmp(a->s,b->s);
}

void exch(void* buff, int i, int j) {
  int size = sizeof(Jval);
	void* tmp = malloc(size);
	memcpy(tmp, (char*)buff+i*size, size);
	memcpy((char*)buff+i*size, (char*)buff+j*size, size);
	memcpy((char*)buff+j*size, tmp, size);
}

void sort(Jval *a, int l, int r, int (*compare)(Jval*,Jval*)) {
  	if(r<=l) return;
  	int i=l-1,j=r;
  	int p=l-1,q=r;
  	while(1)
    {
	    while( compare( a+(++i) , a+r ) < 0 );
	    while( compare( a+r , a+(--j) ) < 0 ) if(j==l) break;
	    if(i>=j) break;
	    exch(a,i,j);
	    if(compare( a+i , a+r ) == 0) exch(a, ++p, i);
	    if(compare( a+j , a+r ) == 0) exch(a, --q, j);
    }
  	exch(a, i, r);
  	j=i-1;
  	i=i+1;
  	for(int k=l;k<=p;k++) exch(a, k, j--);
  	for(int k=r-1;k>=q;k--) exch(a, k, i++);
  	sort(a, l, j, compare);
  	sort(a, i, r, compare);
}

int search_gen(Jval *a, int l, int r, Jval item, int(*compare)(Jval*,Jval*)) {
  if( l > r) return -1;
  int m = l + (r - l)/2;
  if ( compare(&item, a+m) == 0) return m;
  else if ( compare(&item, a+m) > 0 ) return search_gen(a, m+1, r, item, compare);
  else if ( compare(&item, a+m) < 0 ) return search_gen(a, l, m-1, item, compare);
}

void create_array(Jval* a, int size) { 
  srand(time(NULL));
  for (int i = 0; i < size; ++i)
  {
    a[i] = new_jval_i( rand() % 10 );
  }
}

void print(Jval a[], int size) {
  for (int i = 0; i < size; i++)
  {
    printf("%d    ", jval_i(a[i]));
  }
  printf("\n");
}

int main()
{	
  int total = 5;
  Jval *a = (Jval*)malloc( (total+1) * sizeof(Jval));
  a[5] = new_jval_i(5);
  Jval s = new_jval_i(5);
  
  create_array(a,total);
  //print(a,total+1);
  sort(a, 0, total, compare_i);
  int x = search_gen(a, 0, total, s, compare_i);
  printf("%d\n",x );
  print(a,total);
  return 0;
}

