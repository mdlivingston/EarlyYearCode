#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include "node.h"



typedef struct QUEUE {
	SQNode *frontNode;
	SQNode *backNode;
} Queue;

#endif /* Queue_h */

Queue *newQueue();
void enqueue(BSTNode *value, Queue *queue);
BSTNode *dequeue(Queue *queue);
int isEmpty(Queue *queue);
