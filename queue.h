#include <stdlib.h>
#include "node.h"


#ifdef VECTOR_H


struct Queue
{
	size_t head;
	size_t tail;

	size_t msize;
	struct Node **nodes;
};
struct Queue* create_queue(size_t msize);

#elif LIST_H

struct Queue 
{
	struct Node *head;
	struct Node *tail;
};
struct Queue* create_queue();
int push_front_queue (struct Queue *queue,void *data);
struct Node* pop_back_queue (struct Queue *queue);

#endif

int          push_queue(struct Queue *queue, void *data);
void* pop_queue(struct Queue *queue);
void delete_queue(struct Queue *queue);

