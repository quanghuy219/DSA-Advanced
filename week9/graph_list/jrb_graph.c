#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/jrb.h"
#include "lib/dllist.h"

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
    
    Graph tree = jrb_find_int((JRB)jval_v(node->val), v2);
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

void BFS(Graph graph, int start, int stop, void (*func)(int)) {
  Graph node = jrb_find_int(graph, start);
  JRB visited = make_jrb();
  Dllist queue = new_dllist();
  dll_append(queue, new_jval_i(jval_i(node->key)));
  Dllist node_list;
  //int adjacent[100];
  //int totalAdjacentNode;
  
  while(!dll_empty(queue)) {
    node_list = dll_first(queue);
    int u = jval_i(dll_val(node_list));
    dll_delete_node(node_list);
    if(jrb_find_int(visited, u) == NULL) {
      (*func)(u);
      //visited[u] = 1;
      jrb_insert_int(visited, u, new_jval_i(1));
      if(u == stop) break;
      /*
      totalAdjacentNode = getAdjacentVertices(graph,u, adjacent);
      for (int i = 0; i < totalAdjacentNode; i++) {
	if(visited[adjacent[i]] == 0) dll_append(queue, new_jval_i(adjacent[i]));
      }
      */
      
      Graph node_graph = jrb_find_int(graph,u);
      Graph tree = (Graph) jval_v(node_graph->val);
      jrb_traverse(node, tree) {
	if(jrb_find_int(visited, jval_i(node->key)) == NULL) dll_append(queue, new_jval_i(jval_i(node->key)));
      }
    }
  }
}


void DFS(Graph graph, int start, int stop, void (*func)(int)) {
  Graph node = jrb_find_int(graph, start);
  JRB visited = make_jrb();
  Dllist queue = new_dllist();
  dll_append(queue, new_jval_i(jval_i(node->key)));
  Dllist node_list;
  //int adjacent[100];
  //int totalAdjacentNode;
  
  while(!dll_empty(queue)) {
    node_list = dll_last(queue);
    int u = jval_i(dll_val(node_list));
    dll_delete_node(node_list);
    if(jrb_find_int(visited, u) == NULL) {
      (*func)(u);
      //visited[u] = 1;
      jrb_insert_int(visited, u, new_jval_i(1));
      if(u == stop) break;
      /*
      totalAdjacentNode = getAdjacentVertices(graph,u, adjacent);
      for (int i = 0; i < totalAdjacentNode; i++) {
	if(visited[adjacent[i]] == 0) dll_append(queue, new_jval_i(adjacent[i]));
      }
      */
      
      Graph node_graph = jrb_find_int(graph,u);
      Graph tree = (Graph) jval_v(node_graph->val);
      jrb_traverse(node, tree) {
	if(jrb_find_int(visited, jval_i(node->key)) == NULL) dll_append(queue, new_jval_i(jval_i(node->key)));
      }
    }
  }
}
