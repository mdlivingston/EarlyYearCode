#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <stdlib.h>



typedef struct BSTNODE {
	char *value;
    int freq;
    int height;
    int lHeight;
    int rHeight;
    char sign;
	struct BSTNODE *parent;
	struct BSTNODE *left;
	struct BSTNODE *right;
} BSTNode;

typedef struct STACKQEUENODE {
    BSTNode *value;
    struct STACKQEUENODE *nextNode;
    struct STACKQEUENODE *previousNode;
} SQNode;

#endif /* Node_h */


SQNode *newSQNode(BSTNode *value, SQNode *nextNode, SQNode *previousNode);
BSTNode *newBSTNode(char *value);
SQNode *next(SQNode *currentNode);
SQNode *previous(SQNode *currentNode);
