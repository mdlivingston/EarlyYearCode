#ifndef binarysearchtree_h
#define binarysearchtree_h

#include <stdio.h>
#include "node.h"

typedef struct BINARYSEARCHTREE {
	BSTNode *root;
} BinarySearchTree;

#endif /* BinarySearchTree_h */

BinarySearchTree *newBinarySearchTree();
void insertNode(value *value, BinarySearchTree *tree);
void deleteNode(value *value, BinarySearchTree *bst);
BSTNode* searchTree(char *value, BinarySearchTree *tree);
void printTree(BinarySearchTree *tree);
