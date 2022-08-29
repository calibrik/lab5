#include "node.h"
#include <stdlib.h>



struct Node* create_node(void *data)
{
  struct Node *node = calloc(1, sizeof(struct Node));
  // node->next = NULL;
  node->data = data;

  return node;
}
void delete_node(struct Node *node)
{
  free(node);
}
