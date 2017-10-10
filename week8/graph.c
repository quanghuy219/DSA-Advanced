#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *matrix;
  int sizemax;
} Graph;

Graph createGraph(int sizemax) {
  Graph g;
  g.sizemax = sizemax;
  g.matrix = (int*)malloc(sizemax * sizemax * sizeof(int));
  return g;
}

void addEdge(Graph graph, int v1, int v2) {
  graph.matrix[v1 * graph.sizemax + v2] = 1;
  graph.matrix[v2 * graph.sizemax + v1] = 1;
}

int adjacent(Graph graph, int v1, int v2) {
  if (graph.matrix == NULL) return -1;
  return graph.matrix[v1 * graph.sizemax + v2];
}

int getAdjacentVertices(Graph graph, int vertex, int *output) {
  int count = 0;
  if(graph.matrix == NULL) return -1;
  for(int i = 0; i < graph.sizemax; i++) {
    if(graph.matrix[vertex * graph.sizemax + i] == 1) {
      output[count] = i;
      count++;
    }
  }
  return count;
}

