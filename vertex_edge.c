#include "handle.h"
#include "vertex_edge.h"
#include <stdlib.h>
#include <stdio.h>

Edge *create_edge(Vertex *to, int ves) {
    Edge *edge = calloc(1, sizeof(Edge));
    edge->ves = ves;
    edge->to = to;
    return edge;
}

void delete_edge(Edge *edge) {
    free(edge);
}

Vertex *create_vertex(char *key) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    vertex->key = strdup(key);
    return vertex;
}

int remove_edge_vertex(Vertex *from, Vertex *to) {
    if (!from->head) return 1;
    Edge *curr = from->head;
    if (curr->to == to) {
        from->head = curr->next;
        delete_edge(curr);
        return 0;
    }
    while (curr->next) {
        if (curr->next->to == to) break;
        curr = curr->next;
    }
    if (!curr->next) return 1;
    Edge *trash = curr->next;
    curr->next = trash->next;
    delete_edge(trash);
    return 0;
}


void delete_vertex(Vertex *vertex) {
    free(vertex->key);
    while (vertex->head) {
        Edge *trash = vertex->head;
        vertex->head = vertex->head->next;
        delete_edge(trash);
    }
    free(vertex);
}

void add_edge_vertex(Vertex *from, Vertex *to, int ves) {
    Edge *edge = create_edge(to, ves);
    if (!from->head) from->head = edge;
    else {
        Edge *curr = from->head;
        while (curr->next) curr = curr->next;
        curr->next = edge;
    }
}

void display_vertex(Vertex *from) {
    if (!from->head) printf("%s", from->key);
    else {
        printf("%s",from->key);
        Edge *curr = from->head;
        while (curr) {
            printf(" - %s,%d", curr->to->key, curr->ves);
            curr = curr->next;
        }
    }
  printf("\n");
}

