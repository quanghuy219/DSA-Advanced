#include "lib/jrb.h"

#define MAX_SIZE 10

typedef struct {
  JRB edges;
  JRB vertices;
}Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char* getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int *output);
void dropGraph(Graph graph);

void BFS(Graph graph, int start, int stop, void (*func)(int));
int DFS(Graph graph, int start, int stop);
void DFS1(JRB graph, int start, int stop, void (*func)(int));
int DAG(Graph graph);
