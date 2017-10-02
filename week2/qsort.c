#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void create_array(int* a, int size) { 
  srand(time(NULL));
  for (int i = 0; i < size; ++i)
  {
    a[i] = rand() % 10;
  }
}

void swap(int a[], int i, int j){
  int tmp;
   tmp = a[i];
   a[i] = a[j];
   a[j] = tmp; 
} 

void sort(int a[],int l,int r)
{
  if(r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while(a[++i] < a[r] );
      while(a[r]<a[--j]) if(j==l) break;
      if(i>=j) break;
      swap(a,i,j);
      //if(a[i]==a[r]) swap(a,++p,i);
      //if(a[j]==a[r]) swap(a,--q,j);
    }
  swap(a,i,r);
  j=i-1;
  i=i+1;
  //for(int k=l;k<=p;k++) swap(a,k,j--);
  //for(int k=r-1;k>=q;k--) swap(a,k,i++);
  sort(a,l,j);
  sort(a,i,r);
}

void print(int a[], int size) {
  for (int i = 0; i < size; i++)
  {
    printf("%d    ", a[i]);
  }
}

int values[] = { 88, 56, 100, 2, 25 };

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );  
}



int main(){
  
  int size = 10;
  int *a = (int*)malloc(size * sizeof(int));
  create_array(a,size);
  //print(a,size);
  //printf("\n");
  //sort(a,0,size);
  //print(a,size);

  printf("\n");

  printf("Before sorting the list is: \n");
  print(a,size);
  qsort(a, size, sizeof(int), cmpfunc);

  printf("\nAfter sorting the list is: \n");
  print(a,size);
  printf("\n");
   return(0);
}
