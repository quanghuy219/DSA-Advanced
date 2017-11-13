#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb_graph.h"
#include "lib/dllist.h"

Graph createGraph(){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph graph, int id, char *name){
  JRB node = jrb_find_int(graph.vertices, id);
  if(node != NULL){
    printf("vertex %s aleardy exists\n",name );
  }
  else {
   
    jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
  }
}

char* getVertex(Graph graph, int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL) return NULL;
  else return jval_s(node->val);
}

void addEdgeList(Graph graph, int v1, int v2){
  JRB node = jrb_find_int(graph.edges,v1);
  if(node == NULL) {
    JRB tree = make_jrb();
    jrb_insert_int(tree,v2,new_jval_i(1));
    jrb_insert_int(graph.edges,v1, new_jval_v(tree));
  } else {
    JRB tree = (JRB) jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_i(1));
  } 
}

void addEdge(Graph graph, int v1, int v2){
  addEdgeList(graph,v1,v2);
  // addEdgeList(graph,v2,v1);
}

int hasEdge(Graph graph, int v1, int v2) {
  JRB node = jrb_find_int(graph.edges, v1);
  if(node == NULL) return 0;
  else {
    JRB tree = (JRB) jval_v(node->val);
    JRB subNode = jrb_find_int(tree,v2);
    if (subNode == NULL) return 0;
    else return 1;
  }
  return 0;
}

int indegree(Graph graph, int v, int* output){
  JRB vertex;
  int num = 0;
  jrb_traverse(vertex, graph.edges) {
    JRB tree = (JRB) jval_v(vertex->val);
    JRB node = jrb_find_int(tree,v);
    if(node != NULL) {
      int key = jval_i(vertex->key);
      output[num++] = key;
     
    }
  }
  return num;
}



int outdegree(Graph graph, int v, int* output) {
  int num = 0;
  JRB vertex = jrb_find_int(graph.edges, v);
  if(vertex == NULL) return 0;
  else {
    JRB node;
    JRB tree = (JRB) jval_v(vertex->val);
    jrb_traverse(node,tree ) {
      output[num++] = jval_i(node->key);
    }
  }
  return num;
} 

int deleteEdge(Graph graph, int vertex, int value) {
  JRB node = jrb_find_int(graph.edges, vertex);
  if(node == NULL) return 0;

  JRB tree = (JRB) jval_v(node->val);
  JRB nodeTree;
  jrb_traverse(nodeTree, tree) {
    if (jval_i(nodeTree->key) == value) jrb_delete_node(nodeTree);
    return 1;
  } 
  return 0;
}

int DAG(Graph graph) {
  JRB vertex;
  jrb_traverse(vertex, graph.vertices) {
    int hasCycle = DFS(graph, jval_i(vertex->key), -1);
    if(hasCycle == 1) return 0;
  }
  return 1;
}
/*
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



void BFS(Graph graph, int start, int stop, void (*func)(int)) {
  Graph node = jrb_find_int(graph, start);
  JRB visited = make_jrb();
  Dllist queue = new_dllist();
  dll_append(queue, new_jval_i(jval_i(node->key)));
  Dllist node_list;

  
  while(!dll_empty(queue)) {
    node_list = dll_last(queue);
    int u = jval_i(dll_val(node_list));
    dll_delete_node(node_list);
    if(jrb_find_int(visited, u) == NULL) {
      (*func)(u);
      //visited[u] = 1;
      jrb_insert_int(visited, u, new_jval_i(1));
      if(u == stop) break;
 
      
      Graph node_graph = jrb_find_int(graph,u);
      Graph tree = (Graph) jval_v(node_graph->val);
      jrb_traverse(node, tree) {
	if(jrb_find_int(visited, jval_i(node->key)) == NULL) dll_append(queue, new_jval_i(jval_i(node->key)));
      }
    }
  }
}
*/
//void (*func)int
int DFS(Graph graph, int start, int stop) {
  JRB node = jrb_find_int(graph.edges, start);
  if(node == NULL) return 0;
  JRB visited = make_jrb();
  Dllist queue = new_dllist();
  dll_append(queue, new_jval_i(jval_i(node->key)));
  Dllist node_list;
 
  while(!dll_empty(queue)) {
    node_list = dll_first(queue);
    int u = jval_i(dll_val(node_list));
    dll_delete_node(node_list);
   
    if(jrb_find_int(visited, u) == NULL) {
      //(*func)(u);
     
      jrb_insert_int(visited, u, new_jval_i(1));
      if(u == stop) break;
      
      JRB node_graph = jrb_find_int(graph.edges,u);
      if(node_graph != NULL) {
	
      JRB tree = (JRB) jval_v(node_graph->val);
        jrb_traverse(node, tree) {
          if(jrb_find_int(visited, jval_i(node->key)) == NULL) dll_append(queue, new_jval_i(jval_i(node->key)));
          if( jval_i(node->key) == start ) return 1;
        }
      }
    }  
    // else if( u == start) {
    //   return 1;
    //  }
  }
  return 0;
}


void dropGraph(Graph graph) {
  JRB node;
  jrb_traverse(node, graph.edges) {
    jrb_free_tree(jval_v(node->val));
  }
  jrb_free_tree(graph.edges);

  jrb_traverse(node, graph.vertices) {
    jrb_free_tree(jval_v(node->val));
  }
  jrb_free_tree(graph.vertices);
}

void topologicalSort(Graph graph, int* output, int* n) {
  Dllist queue = new_dllist();
  int* out = (int*)malloc(MAX_SIZE * sizeof(int));
  JRB node;
  
  jrb_traverse(node, graph.edges) {
    if( indegree(graph, jval_i(node->key), out) == 0 ) dll_prepend(queue, new_jval_i(jval_i(node->key))); 
  }

  Dllist nodeList;
  
  while(!dll_empty(queue)) {
    nodeList = dll_first(queue);
    int v = jval_i(dll_val(nodeList));
    output[(*n)++] = v;
   
    dll_delete_node(nodeList);
    JRB nodeGraph = jrb_find_int(graph.edges, v);

    if(nodeGraph != NULL) {
      JRB tree = (JRB) jval_v(nodeGraph->val);
      jrb_traverse(node, tree ) {
        deleteEdge(graph, v , jval_i(node->key));
        if(indegree(graph, jval_i(node->key), out) == 0) dll_prepend(queue, new_jval_i(jval_i(node->key)));

      }
    }

  }
}
