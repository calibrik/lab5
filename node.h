#ifdef VECTOR_H

struct Node
{
  void *data;
};


#elif LIST_H

struct Node
{
  void *data;
  struct Node *prev;
  struct Node *next;
};

#endif 

struct Node* create_node(void *data);
void         delete_node(struct Node *node);
