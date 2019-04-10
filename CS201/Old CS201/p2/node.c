#include "node.h"

SQNode *next(SQNode *currentNode) {
	return currentNode->nextNode;
}

SQNode *previous(SQNode *currentNode) {
	return currentNode->previousNode;
}

SQNode *newSQNode(BSTNode *value, SQNode *nextNode, SQNode *previousNode) {
	SQNode *sqNode = malloc(sizeof *sqNode);
	sqNode->value = value;
	sqNode->nextNode = nextNode;
	sqNode->previousNode = previousNode;
	
	return sqNode;
}

BSTNode *newBSTNode(char *value) {
	BSTNode *bstNode = malloc(sizeof *bstNode);
	bstNode->value = value;
    bstNode->freq = 1;
    bstNode->height = 1;
    bstNode->lHeight = 0;
    bstNode->rHeight = 0;
    bstNode->sign = '\0';
	bstNode->left = NULL;
	bstNode->right = NULL;
	bstNode->parent = NULL;
	
	return bstNode;
}
