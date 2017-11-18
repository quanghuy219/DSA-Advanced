#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb_graph.h"
//#include "lib/dllist.h"

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

void addEdgeList(Graph graph, int v1, int v2, double weight){
  JRB node = jrb_find_int(graph.edges,v1);
  if(node == NULL) {
    JRB tree = make_jrb();
    jrb_insert_int(tree,v2,new_jval_d(weight));
    jrb_insert_int(graph.edges,v1, new_jval_v(tree));
  } else {
    JRB tree = (JRB) jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_d(weight));
  } 
}

void addEdge(Graph graph, int v1, int v2, double weight){
  addEdgeList(graph,v1,v2,weight);
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

double getEdgeValue(Graph graph, int v1, int v2) {
  JRB node = jrb_find_int(graph.edges, v1);
  if(node == NULL) return INFINITY_VALUE;

  
  JRB tree = (JRB) jval_v(node->val);
  JRB nodeTree;
  jrb_traverse(nodeTree, tree) {
    if(jval_i(nodeTree->key) == v2) return jval_d(nodeTree->val);
  }
  return INFINITY_VALUE;
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

int DAG(Graph graph) {
  JRB vertex;
  jrb_traverse(vertex, graph.vertices) {
    int hasCycle = DFS(graph, jval_i(vertex->key), -1);
    if(hasCycle == 1) return 0;
  }
  return 1;
}


int getAdjacentVertices(Graph graph, int v, int *output) {
  JRB node = jrb_find_int(graph.edges, v);
  JRB tree = (JRB) jval_v(node->val);
  int total = 0;
  jrb_traverse(node, tree) {
    output[total++] = jval_i(node->key);
  }
  return total;
}

int adjacent(Graph graph, int v1, int v2){
  JRB node = jrb_find_int(graph.edges, v1);
  if(node == NULL) return 0;
  else {

    JRB tree = jrb_find_int((JRB)jval_v(node->val), v2);
    if(tree == NULL) return 0;
    else return 1;
  }
}



void BFS(Graph graph, int start, int stop, Dllist priorityQueue) {
  JRB node = jrb_find_int(graph.edges, start);
  if (node == NULL) return;
  JRB visited = make_jrb();
  Dllist queue = new_dllist();
  dll_append(queue, new_jval_i(jval_i(node->key)));
  Dllist node_list;

  
  while(!dll_empty(queue)) {
    node_list = dll_last(queue);
    int u = jval_i(dll_val(node_list));
    dll_delete_node(node_list);
    if(jrb_find_int(visited, u) == NULL) {
      //(*func)(u);
      
      dll_prepend(priorityQueue, new_jval_i(u));
      jrb_insert_int(visited, u, new_jval_i(1));
      if(u == stop) break;
 
      
      JRB node_graph = jrb_find_int(graph.edges,u);

      if (node_graph == NULL) continue;
      
      JRB tree = (JRB) jval_v(node_graph->val);
      jrb_traverse(node, tree) {
	if(jrb_find_int(visited, jval_i(node->key)) == NULL) dll_prepend(queue, new_jval_i(jval_i(node->key)));
	
      }
    }
  }
}

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

double getPath(JRB d, int u) {
  JRB node = jrb_find_int(d,u);
  if(node == NULL) return INFINITY_VALUE;

  return jval_d(node->val);
}

void relax(Graph graph, JRB d, JRB parent, int u, int v) {
  JRB node_d = jrb_find_int(d,v);
  JRB node_parent = jrb_find_int(parent, v);
  if( getPath(d,v) > getPath(d,u) +  getEdgeValue(graph,u,v)) {
    if(node_d != NULL) {
      double newWeight =  getPath(d,u) +  getEdgeValue(graph,u,v);
      node_d->val = new_jval_d( newWeight );
      node_parent->val = new_jval_i(u); 
    }
  }
}

int deQueue(Dllist queue, JRB d) {
  Dllist min;
  double minDistance = INFINITY_VALUE;
  Dllist node;
  
  dll_traverse(node, queue) {
    JRB nodeTree = jrb_find_int(d, jval_i(dll_val(node)) );
    if(jval_d(nodeTree->val) < minDistance ) {
      minDistance = jval_d(nodeTree->val);
      min = node;
    }
  }
  int shortestNode = jval_i(dll_val(min));;
  dll_delete_node(min);
  return shortestNode;
}

void Dijkstra(Graph graph, int s, JRB d, JRB parent) {
  JRB node;
  Dllist queue = new_dllist();
  jrb_traverse(node, graph.vertices) {
    jrb_insert_int(d, jval_i(node->key), new_jval_d(INFINITY_VALUE) );
    jrb_insert_int(parent, jval_i(node->key), new_jval_v());
    dll_prepend(queue, new_jval_i( jval_i(node->key)) );
  }
  

  node = jrb_find_int(d, s);
  if(node != NULL) node->val = new_jval_d(0);
  
  while(!dll_empty(queue)) {
    int u = deQueue(queue,d);
    JRB nodeTree = jrb_find_int(graph.edges, u);
    if(nodeTree != NULL) {
      JRB tree = (JRB) jval_v(nodeTree->val);
      jrb_traverse(node, tree) {
        relax(graph,d,parent,u,jval_i(node->key));
      }  
    }
  
  }
}



double recurrence(JRB d, JRB parent, int s) {
  JRB node = jrb_find_int(d, s);
  if(node == NULL) return 0;
  JRB nodeParent = jrb_find_int(parent,s);
  printf("%d\n", jval_i(nodeParent->val));
  return jval_d(node->val) + recurrence(d,parent, jval_i(nodeParent->val));
}

double shortestPath(Graph graph, int s, int t, int* path, int* length) {
  JRB d = make_jrb();
  JRB parent = make_jrb();

  Dijkstra(graph, s, d, parent);

  JRB node = jrb_find_int(d, t);
  if(node == NULL) return INFINITY_VALUE;
  double distance = jval_d(node->val);
  return distance;
}
