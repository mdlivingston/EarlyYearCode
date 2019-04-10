#ifndef node_h
#define node_h

#include <stdio.h>
#include <stdlib.h>
#include "value.h"

typedef struct STACKQEUENODE {
    value *value;
    struct STACKQEUENODE *nextNode;
    struct STACKQEUENODE *previousNode;
    struct STACKQEUENODE *parent;
    struct STACKQEUENODE *weight;
    struct STACKQEUENODE *level;
} SQNode;

typedef struct BINHEAP {
    int *value;
    struct BINHEAP *nextNode;
    struct BINHEAP *previousNode;
    double *weight;
    int *level;
    struct BINHEAP *parent;
    struct BINHEAP *child;
} BinHeapNode;
#endif /* Node_h */

BinHeapNode *newBinHeapNode();
SQNode *newSQNode(value *value);
BSTNode *newBSTNode(int *value);
SQNode *next(SQNode *currentNode);
SQNode *previous(SQNode *currentNode);
value *newBSTNodeValue(BSTNode *v);
