#ifndef binarysearchtree_h
#define binarysearchtree_h

#include <stdio.h>
#include "node.h"
#include "queue.h"

typedef struct BINARYSEARCHTREE {
	BSTNode *root;
} BinarySearchTree;

#endif /* BinarySearchTree_h */

BinarySearchTree *newBinarySearchTree();
BSTNode *insertNode(char *value, BinarySearchTree *tree, int *duplicate);
void deleteNode(char *value, BinarySearchTree *bst);
void deleteAVL(BinarySearchTree*B, char* value);
BSTNode* searchTree(char *value, BinarySearchTree *tree);
Queue* buildQueue(BinarySearchTree *tree, int);
int getAvlHeight(BSTNode *node);
int getBalance(BSTNode *node);
BSTNode *avlLeftRightRotate(BSTNode *node);
BSTNode *avlRightLeftRotate(BSTNode *node);
BSTNode *avlRightRightRotate(BSTNode *node);
BSTNode *avlLeftLeftRotate(BSTNode *node);
BSTNode *avlBalanceNode(BSTNode *node, BinarySearchTree*);
void avlBalanceTree(BinarySearchTree *B);
void insertNodeAVL(char* value, BinarySearchTree *tree, int *duplicate);
