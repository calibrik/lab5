#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

Graph *create_graph() {
    Graph *graph = calloc(1, sizeof(Graph));
    graph->size = 3;
    graph->vertexs = calloc(3, sizeof(Vertex *));
    return graph;
}

void set_stuff (Graph *graph,int value)
{
  for (int i = 0; i < graph->size; ++i) {
    if (graph->vertexs[i]) {
      Vertex *curr = graph->vertexs[i];
      while (curr) {
        curr->stuff_from=NULL;
        curr->stuff=value;
        curr = curr->next;
      }
    }
  }
}

size_t hash(char *key, size_t size) {
    size_t hash = 0;
    for (int i = 0; key[i] != '\0'; ++i) {
        hash += hash * 37 + key[i];
    }
    return hash % size;
}

Vertex *search_vertex_graph(Graph *graph, char *key) {
    size_t hash_key = hash(key, graph->size);
    if (!graph->vertexs[hash_key]) return NULL;
    Vertex *curr = graph->vertexs[hash_key];
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

int display_graph(Graph *graph) {
    if (graph->busy == 0) return NOTHING_GRAPH;
    printf("\n");
    for (int i = 0; i < graph->size; ++i) {
        if (graph->vertexs[i]) {
            Vertex *curr = graph->vertexs[i];
            while (curr) {
                display_vertex(curr);
                curr = curr->next;
            }
        } //else printf("%p\n", graph->vertexs[i]);
    }
    printf("\n");
    return OK;
}

void reorg_hash (Graph *graph)
{
  graph->busy = 0;
  Vertex **copy_vertexs=calloc(graph->size,sizeof(Vertex*));
  memcpy(copy_vertexs,graph->vertexs,sizeof(Vertex*)*graph->size);
  graph->size *=2;
  free(graph->vertexs);
  graph->vertexs=calloc(graph->size,sizeof(Vertex*));
  for (int i = 0; i<graph->size/2; ++i) {
      Vertex *curr = copy_vertexs[i];
      while (curr) {
              Vertex *new = curr;
              curr = curr->next;
              add_vertex_graph(graph, new->key, new);
      }
  }
  free(copy_vertexs);
}

int add_vertex_graph(Graph *graph, char *key, Vertex *new) {
    size_t hash_key = hash(key, graph->size);
    Vertex *check = search_vertex_graph(graph, key);
    if (check) return EXIST_VERTEX;
    if (new) {
        new->prev = NULL;
        new->next = NULL;
    }
    else new=create_vertex(key);
    if (graph->size==graph->busy)
    {
      reorg_hash(graph);
      hash_key=hash(key, graph->size);
    }
    if (graph->vertexs[hash_key]) {
      graph->vertexs[hash_key]->prev=new;
      new->next=graph->vertexs[hash_key];
      graph->vertexs[hash_key]=new;
    } else {
        graph->vertexs[hash_key] = new;
        graph->busy++;
    }
    return OK;
}

int delete_graph(Graph *graph) {
    for (int i = 0; i < graph->size; ++i) {
        if (graph->vertexs[i]) {
            Vertex *trash = graph->vertexs[i];
            while (graph->vertexs[i]) {
                trash = graph->vertexs[i];
                graph->vertexs[i] = graph->vertexs[i]->next;
                delete_vertex(trash);
            }
        }
    }
    free(graph->vertexs);
    free(graph);
    return OK;
}


int add_edge_graph(Graph *graph, char *key_from, char *key_to, int ves) {
    if (graph->busy == 0) return NOTHING_GRAPH;
    if (strcmp(key_to, key_from) == 0) return SAME_VERTEXS;
    Vertex *from = search_vertex_graph(graph, key_from);
    Vertex *to = search_vertex_graph(graph, key_to);
    if (!to || !from) return NOT_EXIST_VERTEX;
    Edge *curr = from->head;
    while (curr) {
        if (curr->to == to) return EXIST_EDGE;
        curr = curr->next;
    }
    add_edge_vertex(from, to, ves);
    return OK;
}

int remove_edge_graph(Graph *graph, char *key_from, char *key_to) {
    if (graph->busy == 0) return NOTHING_GRAPH;
    if (strcmp(key_to, key_from) == 0) return SAME_VERTEXS;
    Vertex *from = search_vertex_graph(graph, key_from);
    Vertex *to = search_vertex_graph(graph, key_to);
    if (!to || !from) return NOT_EXIST_VERTEX;
    if (remove_edge_vertex(from, to) == 1) return NOT_EXIST_EDGE;
    return OK;
}

int remove_vertex_graph(Graph *graph, char *key) {
    if (graph->busy == 0) return NOTHING_GRAPH;
    Vertex *trash = search_vertex_graph(graph, key);
    if (!trash) return NOT_EXIST_VERTEX;
    for (int i = 0; i < graph->size; ++i) {
        if (graph->vertexs[i]) {
            Vertex *curr = graph->vertexs[i];
            while (curr) {
                remove_edge_vertex(curr, trash);
                curr = curr->next;
            }
        }
    }
    if (trash->prev) {
        if (trash->next) {
            trash->prev->next = trash->next;
            trash->next->prev = trash->prev;
        } else trash->prev->next = NULL;
    } else {
        graph->busy--;
        if (trash->next) {
            graph->vertexs[hash(key, graph->size)] = trash->next;
            trash->next->prev = NULL;;
        } else graph->vertexs[hash(key, graph->size)] = NULL;
    }
    delete_vertex(trash);
    return OK;
}

void path_count(Graph *graph,Vertex *to, Vertex *from)
{
  long long sum_ves=0;
  printf("%s",to->key);
  Vertex **ptr=&to->stuff_from;
  sum_ves+=to->stuff;
  to=to->stuff_from;
  *ptr=NULL;

  while (to)
  {
    ptr=&to->stuff_from;
    sum_ves+=to->stuff;
    printf(" <- %s",to->key);
    to=to->stuff_from;
    *ptr=NULL;
  }
  printf("\nFinal weight:%lld\n",sum_ves);
}

int weight_search_graph (Graph *graph, char* key_from, char* key_to)
{
  if (graph->busy == 0) return NOTHING_GRAPH;
  if (strcmp(key_to, key_from) == 0) return SAME_VERTEXS;
  Vertex *from = search_vertex_graph(graph, key_from);
  Vertex *to = search_vertex_graph(graph, key_to);
  if (!to || !from) return NOT_EXIST_VERTEX;
  set_stuff(graph,0);
  struct Queue *queue=create_queue();
  push_queue(queue,from);
  while (queue->head)
  {
    Vertex *vert=queue->head->data;
    if (vert->head)
    {
      Edge *curr=vert->head;
      while (curr)
      {
        if (!curr->to->stuff_from)
        {
          push_queue(queue,curr->to);
          curr->to->stuff_from=vert;
          curr->to->stuff=curr->ves;
        }
        curr=curr->next;
      }
    }
    if (vert==to)
    { 
      path_count(graph,to,from);
      delete_queue(queue);
      return OK;
    }
    delete_node(pop_queue(queue));
  }
  delete_queue(queue);
  return NO_PATH;
}

int belmond_ford_graph(Graph *graph, char * key_from, char* key_to)
{
  if (graph->busy == 0) return NOTHING_GRAPH;
  if (strcmp(key_to, key_from) == 0) return SAME_VERTEXS;
  Vertex *from = search_vertex_graph(graph, key_from);
  Vertex *to = search_vertex_graph(graph, key_to);
  if (!to || !from) return NOT_EXIST_VERTEX;
  set_stuff(graph,INT_MAX); 
  from->stuff=0;
  for (int a=0;a<graph->busy-1;++a)
  {
  for (int i=0;i<graph->size;++i)
  {
    Vertex *vertex=graph->vertexs[i];
    while (vertex) 
    {
      Edge *curr=vertex->head;
      while (curr)
      {
        if (vertex->stuff!=INT_MAX && vertex->stuff+curr->ves<curr->to->stuff)
        {
          curr->to->stuff_from=vertex;
          curr->to->stuff=vertex->stuff+curr->ves;
        }
        curr=curr->next;
      }
      vertex=vertex->next;
    }

      }
  }
/*  for (int i=0;i<graph->size;++i)
  {
    if (graph->vertexs[i]) {
      Vertex *curr = graph->vertexs[i];
      while (curr) {
        printf("%s %d\n",curr->key,curr->stuff); 
        curr = curr->next;
      }
    }
  } вывод веса вершин*/
  printf("Final weight:%d\n",to->stuff);
 
  while (to)
  {
    Vertex **ptr=&to->stuff_from;
    printf("%s\n",to->key);
    to=to->stuff_from;
    *ptr=NULL;
  }
  return OK;
}

void bfs_in(Vertex *curr)
{
  //if (curr->staff==2) return;
  Edge *edge=curr->head;
  curr->stuff++;
  while (edge)
  {
    if (edge->to->stuff<2) bfs_in(edge->to);
    edge=edge->next;
  }
}

void bfs_out(struct Queue *queue,Vertex *curr)
{
  curr->stuff=1;
  Edge *edge=curr->head;
  while (edge)
  {
    if (edge->to->stuff!=1) bfs_out(queue,edge->to);
    edge=edge->next;
  }
  push_queue(queue,curr);
}

int find_connects_graph(Graph *graph)
{ 
  if (graph->busy == 0) return NOTHING_GRAPH;
  set_stuff(graph,0);
  struct Queue *queue=create_queue();
  for (int i=0;i<graph->size;++i)
  {
    if (graph->vertexs[i]&&graph->vertexs[i]->stuff==0)
    {
      bfs_out(queue,graph->vertexs[i]);
    }
  } 
 /*struct Node *curr=queue->head;
 Vertex *data;
 while (curr)
 {
   data=curr->data;
   printf("%s\n",data->key);
   curr=curr->next;
 }*/
 char group='A';
 Vertex *vert=pop_queue(queue);
  while (vert)
  {
    if (vert->stuff!=2){
      bfs_in(vert);
      printf("\t\tGroup %c\n",group);
      printf("%s\n",vert->key);
      group++;
    }
    else{
      printf("%s\n",vert->key);
    }
    vert=pop_queue(queue);
  }
  delete_queue(queue); 
  return OK;
}
