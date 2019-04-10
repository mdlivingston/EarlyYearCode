
#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "sll.h"

typedef struct QUEUE{
    sll *list;
} queue;

queue *newQueue(void (*d)(FILE *,void *));   //constructor
extern void enqueue(queue *items,void *value);      //stores a generic value
extern void *dequeue(queue *items);                 //returns a generic value
extern void *peekQueue(queue *items);               //returns a generic value
extern void displayQueue(FILE *fp,queue *items);
int sizeQueue(queue *items);
#endif /* queue_h */
