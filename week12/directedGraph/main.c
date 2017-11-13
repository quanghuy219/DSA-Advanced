#include <stdio.h>
#include <stdlib.h>
#include "jrb_graph.h"

void printVertex(int v) {
  printf("%4d",v);
}
int main()
{
  //int i, n, output[100];
  
  Graph g = createGraph();
  addVertex(g,0,"V0");
  addVertex(g,1,"V1");
  addVertex(g,2,"V2");
  addVertex(g,3,"V3");
  
  addEdge(g,0,1);
  addEdge(g, 1, 2);
  addEdge(g, 2, 0);
  addEdge(g, 1, 3);
  
  
  if( DAG(g) ) printf("the graph is acycle\n");
  else printf("Have cycles in the graph\n");
  
 
return 0;
}

