#ifndef VERTEX_EDGE_H
#define VERTEX_EDGE_H

typedef struct Vertex Vertex;

typedef struct Edge {
    int ves;
    Vertex *to;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    Vertex *stuff_from;
    char *key;
    int stuff;
    Edge *head;
    Vertex *next;
    Vertex *prev;
} Vertex;



Edge *create_edge(Vertex *to, int ves);
void delete_edge(Edge *);
Vertex *create_vertex(char *key);
void delete_vertex(Vertex *vertex);
void add_edge_vertex(Vertex *from, Vertex *to, int ves);
int remove_edge_vertex(Vertex *from, Vertex *to);
void display_vertex(Vertex *from);

#endif
