#include "queue.h"

Queue *newQueue() {
	
	Queue *newQueue = malloc(sizeof *newQueue);
	newQueue->frontNode = NULL;
	newQueue->backNode = NULL;
	
	return newQueue;
}

void enqueue(BSTNode *value, Queue *queue) {
	SQNode *node = newSQNode(value, queue->frontNode, NULL);
	
	if (queue->frontNode != NULL) {
		queue->frontNode->previousNode = node;
	} else {
		queue->backNode = node;
	}
	
	node->nextNode = queue->frontNode;
	queue->frontNode = node;
}

BSTNode *dequeue(Queue *queue) {
	if (queue->frontNode != NULL) {
		SQNode *backNode = queue->backNode;
		BSTNode *value = backNode->value;
		
		if (queue->backNode == queue->frontNode) {
			queue->frontNode = NULL;
		}
		queue->backNode = backNode->previousNode;
		backNode = NULL;
		free(backNode);
		
		return value;
	}
	return 0;
}


int isEmpty(Queue *queue) {
	if (queue->frontNode) {
		return 0;
	}
	return 1;
}
