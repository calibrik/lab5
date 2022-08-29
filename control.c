#include "handle.h"
#include "control.h"
#include <stdlib.h>
#include <stdio.h>

void load_graph_file(struct Control *control) {
  char *filename = get_str("filename");
  FILE *file = fopen(filename, "r");
  free(filename);
  if (!file) {
    printf("File not found\n");
  }
  else {
    char key_from[30];
    int ves;
    char type;
    char key_to[30];
    while (!feof(file)) {
      if (fscanf(file, "%s\n", &type) == 1)
      {
        if (type=='v')
        {
          fscanf(file,"%s\n",key_from);
          add_vertex_graph(control->graph,key_from,NULL);
        }
        else
        {
          fscanf(file,"%s\n%d\n%s\n",key_from, &ves,key_to);
          add_edge_graph(control->graph,key_from,key_to,ves);
        }
      }
    }
    fclose(file);
  }
}

Control *create_control() {
  Control *control = malloc(sizeof(Control));
  control->graph = create_graph();
  char choice;
  printf("Load from file? (y/n): ");
  scanf("%c%*c", &choice);
  if (choice == 'y')
    load_graph_file(control);

    return control;
}

const char *show_status(int index) {
    switch (index) {
        case OK:
            return "Ok";
        case NOTHING_GRAPH:
            return "Nothing in graph";
        case NOT_EXIST_EDGE:
            return "Not exist edge";
        case NOT_EXIST_VERTEX:
            return "Not exist vertex";
        case EXIST_VERTEX:
            return "Already exist vertex";
        case EXIST_EDGE:
            return "Already exist edge";
        case SAME_VERTEXS:
            return "Same vertexs";
        case NO_PATH:
            return "Not found path";
        default:
            return "Unknown status";
    }
}

void delete_control(Control *control) {
    printf("%s\n", show_status(delete_graph(control->graph)));
    free(control);
}

void add_vertex(Control *control) {
    char *key = get_str("key");
    printf("%s\n", show_status(add_vertex_graph(control->graph, key, NULL)));
    free(key);
}

void display(Control *control) {
    printf("%s\n", show_status(display_graph(control->graph)));
}

void add_edge(Control *control) {
    char *key_from = get_str("from key");
    char *key_to = get_str("to key");
    int ves;
    printf("Enter ves: ");
    scanf("%d", &ves);
    printf("%s\n", show_status(add_edge_graph(control->graph, key_from, key_to, ves)));
    free(key_from);
    free(key_to);
}

void remove_edge(Control *control) {
    char *key_from = get_str("from key");
    char *key_to = get_str("to key");
    printf("%s\n", show_status(remove_edge_graph(control->graph, key_from, key_to)));
    free(key_from);
    free(key_to);
}

void remove_vertex(Control *control) {
    char *key = get_str("key");
    printf("%s\n", show_status(remove_vertex_graph(control->graph, key)));
    free(key);
}
void weight_search(Control *control)
{
  char *key_from = get_str("from key");
  char *key_to = get_str("to key");
  printf("%s\n",show_status( weight_search_graph (control->graph,key_from,key_to)));
  free(key_from);
  free(key_to);

}

void belmond_ford(Control *control)
{
  char *key_from = get_str("from key");
  char *key_to = get_str("to key");
  printf("%s\n",show_status( belmond_ford_graph (control->graph,key_from,key_to)));
  free(key_from);
  free(key_to);

}

void find_connections(Control *control)
{ 
  printf("%s\n",show_status( find_connects_graph (control->graph)));
}
