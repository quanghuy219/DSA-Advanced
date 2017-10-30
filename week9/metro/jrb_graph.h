#include "lib/jrb.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, char* s1, char* v2);
int adjacent(Graph graph, char* v1, char* v2);
int getAdjacentVertices(Graph graph, char* vertex, char* output);
void dropGraph(Graph graph);

void BFS(Graph graph, char* start, char* stop, void (*func)(char*));
void DFS(Graph graph, char* start, char* stop, void (*func)(char*));
int findShortestPath(Graph graph, char* start, char* stop);
