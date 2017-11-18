#include "lib/jrb.h"
#include "lib/dllist.h"

#define MAX_SIZE 10
#define INFINITY_VALUE 100000

typedef struct {
  JRB edges;
  JRB vertices;
}Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char* getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
int hasEdge(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int *output);
void dropGraph(Graph graph);

void BFS(Graph graph, int start, int stop,Dllist queue);
int DFS(Graph graph, int start, int stop);
void DFS1(JRB graph, int start, int stop, void (*func)(int));
int DAG(Graph graph);
double shortestPath(Graph graph, int s, int t, int* path, int* length);
