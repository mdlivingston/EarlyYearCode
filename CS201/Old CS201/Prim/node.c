#include "node.h"

SQNode *next(SQNode *currentNode) {
    return currentNode->nextNode;
}

SQNode *previous(SQNode *currentNode) {
    return currentNode->previousNode;
}

SQNode *newSQNode(value *value) {
    SQNode *sqNode = malloc(sizeof *sqNode);
    sqNode->value = value;
    sqNode->nextNode = NULL;
    sqNode->previousNode = NULL;
    sqNode->parent = NULL;
    sqNode->weight = NULL;
    sqNode->level = NULL;
    
    return sqNode;
}

BSTNode *newBSTNode(int *value) {
    BSTNode *bstNode = malloc(sizeof *bstNode);
    bstNode->value = *value;
    bstNode->child = NULL;
    bstNode->nextNode = NULL;
    bstNode->previousNode= NULL;
    
    return bstNode;
}

BinHeapNode *newBinHeapNode() {
    BinHeapNode *binHeap = malloc(sizeof(binHeap));
    binHeap->nextNode = NULL;
    binHeap->previousNode = NULL;
    binHeap->value = 0;
    binHeap->weight = NULL;
    binHeap->level = NULL;
    binHeap->parent = NULL;
    binHeap->child = NULL;
    return binHeap;
}

