#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "vertex_edge.h"
#include "queue.h" 

enum Status
{
  OK,
  NOTHING_GRAPH,
  NOT_EXIST_EDGE,
  NOT_EXIST_VERTEX,
  EXIST_VERTEX,
  EXIST_EDGE,
  NO_PATH,
  SAME_VERTEXS,
};

typedef struct Graph
{
  size_t busy; // ?
  size_t size;
  Vertex **vertexs;
}Graph;

Graph* create_graph();
size_t hash(char* key,size_t size);
int add_vertex_graph (Graph *graph,char* key,Vertex *new);
int delete_graph(Graph *graph);
int display_graph (Graph *graph);
Vertex* search_vertex_graph(Graph *graph, char *key);
int add_edge_graph(Graph *graph,char* key_from,char* key_to,int ves);
int remove_edge_graph (Graph *graph,char* key_from,char* key_to);
int remove_vertex_graph (Graph *graph,char* key);
int weight_search_graph (Graph *graph, char* key_from, char* key_to);
void path_count(Graph *graph,Vertex *to, Vertex *from);
int belmond_ford_graph(Graph *graph, char * key_from, char* key_to);
void set_stuff (Graph *graph,int value);
void bfs_out(struct Queue *stack,Vertex *curr);
int find_connects_graph(Graph *graph);

#endif
