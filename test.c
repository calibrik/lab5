#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
  struct Queue *queue=create_queue();
  int val=1;
  push_queue(queue,&val);
  int val1=2;
  push_queue(queue,&val1);
  int val2=3;
  push_front_queue(queue,&val2);

  struct Node* curr=queue->head;
  while (curr) 
  {
    printf("%d->",*(int*)curr->data);
    curr=curr->next;
  }
  printf("\n");
  curr=queue->tail;
  while (curr) 
  {
    printf("%d->",*(int*)curr->data);
    curr=curr->prev;
  }
  printf("\n");
  delete_queue(queue);
  return 0;
}
