#include "queue.h"


Queue *newQueue() {
    
    Queue *newQueue = malloc(sizeof *newQueue);
    newQueue->frontNode = NULL;
    newQueue->backNode = NULL;
    
    return newQueue;
}

void enqueue(value *value, Queue *queue) {
    SQNode *node = newSQNode(value);
    
    if (queue->frontNode != NULL) {
        queue->frontNode->previousNode = node;
    } else {
        queue->backNode = node;
    }
    
    node->nextNode = queue->frontNode;
    queue->frontNode = node;
}

value *dequeue(Queue *queue) {
    if (queue->frontNode != NULL) {
        SQNode *backNode = queue->backNode;
        value *value = NULL;
        if(backNode){
            value = backNode->value;
        }
        if (queue->backNode == queue->frontNode) {
            queue->frontNode = NULL;
        }
        if(backNode){
        queue->backNode = backNode->previousNode;
        }
        backNode = NULL;
        free(backNode);
        
        return value;
    }
    return 0;
}

