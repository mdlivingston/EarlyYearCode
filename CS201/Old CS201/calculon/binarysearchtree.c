#include "binarysearchtree.h"

unsigned long hash(char *str) {
	unsigned long hash = 5381;
	int c;
	
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	
	return hash;
}

BinarySearchTree *newBinarySearchTree() {
	BinarySearchTree *bst = malloc(sizeof *bst);
	bst->root = 0;
	
	return bst;
}

void insertNode(value *value, BinarySearchTree *tree) {
	BSTNode *root = tree->root;
	unsigned long key = hash(value->sval);
	
	if(root == 0) {
		root = newBSTNode(value);
	} else {
		int isLeft  = 0;
		BSTNode* currentNode = root;
		BSTNode* parentNodev = 0;
		
		while(currentNode != 0) {
			parentNodev = currentNode;
			if (key < hash(currentNode->value->sval)) {
				isLeft = 1;
				currentNode = currentNode->left;
			} else if (key > hash(currentNode->value->sval)) {
				isLeft = 0;
				currentNode = currentNode->right;
			} else {
				currentNode->value = value;
				return;
			}
			
		}
		if(isLeft) {
			parentNodev->left = newBSTNode(value);
		} else {
			parentNodev->right = newBSTNode(value);
		}
		
	}
	
	tree->root = root;
}

BSTNode *recursiveDelete(value *value, BSTNode *root) {
	if(root == 0) {
		return 0;
	}
	
	BSTNode *currentNode;
	if(value->sval[0] < root->value->sval[0]) {
		root->left = recursiveDelete(value, root->left);
	} else if(value->sval[0] > root->value->sval[0]) {
		root->right = recursiveDelete(value, root->right);
	} else {
		if (root->left == 0) {
			currentNode = root->right;
			free(root);
			root = currentNode;
		} else if (root->right == 0) {
			currentNode = root->left;
			free(root);
			root = currentNode;
		} else {
			currentNode = root->right;
			BSTNode *parent = 0;
			
			while(currentNode->left != 0)
			{
				parent = currentNode;
				currentNode = currentNode->left;
			}
			root->value = currentNode->value;
			if (parent != 0) {
				parent->left = recursiveDelete(parent->left->value, parent->left);
			} else {
				root->right = recursiveDelete(root->right->value, root->right);
			}
		}
	}
	return root;
}

void deleteNode(value *value, BinarySearchTree *tree) {
	tree->root = recursiveDelete(value, tree->root);
}

BSTNode* searchTree(char *value, BinarySearchTree *tree) {
	BSTNode *root = tree->root;
	unsigned long key = hash(value);
	
	if(root == 0) {
		return 0;
	}
	
	BSTNode* currentNode = root;
	while(currentNode != 0) {
		if (key < hash(currentNode->value->sval)) {
			currentNode = currentNode->left;
		} else if (key > hash(currentNode->value->sval)) {
			currentNode = currentNode->right;
		} else {
			return currentNode;
		}
			
	}
	
	return currentNode;
}

void recursivePrint(BSTNode *root) {
	if (root == 0) {
		return;
	}
	printf("%lf ", root->value->rval);
	recursivePrint(root->left);
	recursivePrint(root->right);
}

void printTree(BinarySearchTree *tree) {
	recursivePrint(tree->root);
	printf("\n");
}
