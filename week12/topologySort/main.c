#include <stdio.h>
#include <stdlib.h>
#include "jrb_graph.h"

void printVertex(int v) {
  printf("%4d",v);
}
int main()
{
  int n;
  int* output = (int*)malloc(100 * sizeof(int));
  
  Graph g = createGraph();
  addVertex(g,0,"CS102");
  addVertex(g,1,"CS140");
  addVertex(g,2,"CS160");
  addVertex(g,3,"CS301");
  addVertex(g,4,"CS311");
  addVertex(g,5,"MATH300");
  
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 3);
  addEdge(g, 5, 4);
  addEdge(g, 3, 4);
  
  
  if( !DAG(g) ) {
    printf("Cannot make topological sort\n");
    return 1;
  }

  topologicalSort(g,output,&n);
  for (int i = 0; i < n; i++)
  {
    printf("%s\n", getVertex(g, output[i]) );
  }
 
return 0;
}

