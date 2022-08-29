#include "queue.h"


#ifdef VECTOR_H

struct Queue* create_queue(size_t msize)
{
	struct Queue *queue=calloc(1,sizeof(struct Queue));
	queue->msize=msize;
	queue->nodes=calloc(msize,sizeof(struct Nodes*));

	return queue;
}
void delete_queue(struct Queue *queue)
{
  struct Node *trash = NULL;
  while ((trash = pop_queue(queue)) != NULL)
  {
    free(trash);
  }

  free(queue->nodes);
  free(queue);
}
int push_queue(struct Queue *queue, void *data) {
  if (queue->nodes[ queue->tail ] != NULL) // Заполнена
  { return 1; } // FAIL_ADD

	queue->nodes[queue->tail] = create_node(data);
  queue->tail = (queue->tail + 1) % queue->msize;

	return 0; // SUCCESS_ADD
}
struct Node* pop_queue(struct Queue *queue)
{	
  struct Node *node = NULL;
  if (queue->nodes[ queue->head ] != NULL)
  {
    node = queue->nodes[queue->head];
    queue->nodes[ queue->head ] = NULL;
    queue->head = (queue->head + 1) % queue->msize;
  }

  return node;
}

#elif LIST_H

struct Queue* create_queue()
{
	return calloc(1, sizeof(struct Queue));
}
void delete_queue(struct Queue *queue)
{
  struct Node *trash = NULL;
	while (queue->head != NULL)
	{
    trash = queue->head;
    queue->head=queue->head->next;
    delete_node(trash);
	}
	free(queue);
}
int push_queue(struct Queue *queue, void *data) {
	struct Node *new = create_node(data);
	if (queue->tail==NULL)
		queue->head=new;
	else
  {
    new->prev=queue->tail;
		queue->tail->next=new;
  }
  queue->tail = new;

	return 0;
}
void* pop_queue(struct Queue *queue) {
	if (queue->head==NULL)
  { return NULL; }

	struct Node *curr=queue->head;
	queue->head=queue->head->next;
  if (queue->head) queue->head->prev=NULL;
  void *data=curr->data;
  delete_node(curr);
	return data;
}

int push_front_queue (struct Queue *queue,void *data)
{
  struct Node *new = create_node(data);
	if (queue->head==NULL)
		queue->tail=new;
	else
  {
    new->next=queue->head;
    queue->head->prev=new;
  }
  queue->head = new;

	return 0;

}

struct Node* pop_back_queue (struct Queue *queue)
{
  if (queue->tail==NULL)
  { return NULL; }

	struct Node *curr=queue->tail;
	queue->tail=queue->tail->prev;
  queue->tail->next=NULL;
	curr->prev = NULL;

	return curr;

}


#endif
