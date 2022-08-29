all:
				clang main.c handle.c control.c graph.c vertex_edge.c queue.c node.c -DLIST_H
				valgrind --leak-check=full ./a.out
