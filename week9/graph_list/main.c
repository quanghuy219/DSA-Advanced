#include <stdio.h>
#include <stdlib.h>
#include "jrb_graph.h"

void printVertex(int v) {
  printf("%4d",v);
}

int main()
{
  //int i, n, output[100];
  Graph g = createGraph(100);
  addEdge(g,0,1);
  addEdge(g,1,2);
  addEdge(g,1,3);
  addEdge(g,2,3);
  addEdge(g,2,4);
  addEdge(g,4,5);
  /*
  n = getAdjacentVertices(g,1,output);
  if(n == 0) printf("No adjacent vetices of node 1\n");
  else {
    printf("Adjacent vertices of node 1:\n");
    for (i = 0; i < n; ++i) {
      printf("%5d\n",output[i]);
    }

  }
  */

  
  printf("\nBFS start from node 1 to 5: ");
  BFS(g,1,5,printVertex);
  printf("\nDFS start from node 1 to all: ");
  DFS(g, 1,-1, printVertex);
  printf("\n");
  return 0;
}

