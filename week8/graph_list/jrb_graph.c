#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"

typedef JRB Graph;

Graph createGraph(){
  Graph g = make_jrb();
  return g;
}

void addEdgeList(Graph graph, int v1, int v2){
  Graph node = jrb_find_int(graph,v1);
  if(node == NULL) {
    Graph tree = make_jrb();
    jrb_insert_int(graph,v1, new_jval_v(tree));
    jrb_insert_int(tree,v2,new_jval_i(1));
  } else {
    Graph tree = (JRB) jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_i(1));
  } 
}

void addEdge(Graph graph, int v1, int v2){
  addEdgeList(graph,v1,v2);
  addEdgeList(graph,v2,v1);
}

int adjacent(Graph graph, int v1, int v2){
  Graph node = jrb_find_int(graph, v1);
  if(node == NULL) return 0;
  else {
    Graph tree = jrb_find_int( (JRB) jval_v(node->val), v2);
    if(tree == NULL) return 0;
    else return 1;
  }
}

int getAdjacentVertices(Graph graph, int v, int *output) {
  Graph node = jrb_find_int(graph, v);
  Graph tree = (JRB) jval_v(node->val);
  int total = 0;
  jrb_traverse(node, tree) {
    output[total++] = jval_i(node->key);
  }
  return total;
}

void dropGraph(Graph graph) {
  JRB node;
  jrb_traverse(node, graph) {
    jrb_free_tree(jval_v(node->val));
  }
}
