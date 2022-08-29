#ifndef CONTROL_H
#define CONTROL_H

#include "graph.h"

typedef struct Control {
    Graph *graph;
} Control;

Control *create_control();
const char *show_status(int index);
void delete_control(Control *control);
void add_vertex(Control *control);
void display(Control *control);
void add_edge(Control *control);
void remove_edge(Control *control);
void remove_vertex(Control *control);
void weight_search(Control *control);
void belmond_ford(Control *control);
void find_connections(Control *control);

#endif
