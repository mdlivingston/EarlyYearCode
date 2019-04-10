#include "binarysearchtree.h"
#include "string.h"
#include "queue.h"
#include "stdlib.h"


BinarySearchTree *newBinarySearchTree() {
    BinarySearchTree *bst = malloc(sizeof *bst);
    bst->root = 0;
    
    return bst;
}

BSTNode* sibling(BSTNode* node){
    if (node == node->parent->left){
        return node->parent->right;
    }
    if (node == node->parent->right){
        return node->parent->left;
    }
    else{
        return 0;
    }
    
}

int height(BSTNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else{
        int lheight = height(node->left);
        int rheight = height(node->right);
        
        if (lheight > rheight)
        {
            
            return lheight + 1;
        }
        
        return rheight + 1;
    }
}

int getBalance(BSTNode *node){
    int lHeight = 0;
    int rHeight = 0;
    if(node == NULL) return 0;
    if(node->left){
        lHeight = node->left->height;
    }
    if(node->right){
        rHeight = node->right->height;
    }
    return lHeight - rHeight;
    
}

int max(int a, int b){
    return (a>b)? a: b;
}

BSTNode *getFavoriteChild(BSTNode *node) {
    if(!node){
        return 0;
    }
    if( node->left == NULL && node->right == NULL) {
        return 0;
    }
    if(node->left && node->right == NULL){
        return node->left;
    }
    if(node->right && node->left == NULL){
        return node->right;
    }
    if (node->left->height > node->right->height) {
        return node->left;
    }
    if (node->right->height > node->left->height) {
        return node->right;
    }
    return 0;
}



int isLinear(BSTNode *favoriteChild, BSTNode *node, BSTNode *parent) {
    if(parent){
        if ((favoriteChild == node->left && node == parent->left) || (favoriteChild == node->right && node == parent->right)) {
            return 1;
        }
    }
    return 0;
}

BSTNode* rotateright(BSTNode *node)
{
    BSTNode *k1 = node;
    BSTNode *k2= k1->parent;
    BSTNode *y = k1->right;
    BSTNode *x = k1->left;
    
    x->parent = k1;
    if(k2 && k2->parent){
        if(!isLinear(k1, k2, k2->parent)){
            k2->parent->right = k1;
        }
        else{
            k2->parent->left = k1;
        }
    }
    k1->right = k2;
    k2->left = y;
    k1->parent = k2->parent;
    k2->parent = k1;
    
    
    
    
    return(k1);
}

BSTNode * rotateleft(BSTNode *node)
{
    BSTNode *k2 = node;
    BSTNode *k1= node->parent;
    BSTNode *y = k2->left;
    
    if(k1){
        k2->parent = k1->parent;
    }
    if(k1 && k1->parent){
        if(!isLinear(k2, k1, k1->parent)){
            k1->parent->left = k2;
        }
        else{
            k1->parent->right = k2;
        }
    }
    
    k1->right = y;
    k2->left = k1;
    k1->parent = k2;
    
    
    
    return(k2);
}

BSTNode * rotateLeftRight(BSTNode*node){
    BSTNode* k1 = node->parent;
    BSTNode* k2 = node->left;
    BSTNode* k3 = node;
    BSTNode*b = k2->left;
    BSTNode*c = k2->right;
    if( k1 && k1->parent){
        if(!isLinear(k3, k1, k1->parent)){
            k1->parent->left = k2;
        }
        else{
            k1->parent->right = k2;
        }
    }
    if(k1){
        k2->parent = k1->parent;
        
        k1->right = b;
    }
    k3->left = c;
    k2->left = k1;
    k2->right = k3;
    k3->parent = k2;
    k1->parent = k2;
    if(k1 && k1->right){
        k1->right->parent = k1;
    }
    
    return (k3);
    
}
BSTNode* rotateRightLeft(BSTNode *node){
    BSTNode* k1 = node;
    BSTNode* k2 = k1->right;
    BSTNode* k3 = k1->parent;
    BSTNode*b = k2->left;
    BSTNode*c = k2->right;
    if(k3 && k3->parent){
        if(!isLinear(k1, k3, k3->parent)){
            k3->parent->right = k2;
        }
        else{
            k3->parent->left = k2;
        }
    }
    k1->right = b;
    if(k3){
        k3->left = c;
    }
    k2->left = k1;
    k2->right = k3;
    k1->parent = k2;
    if(k3){
        k2->parent = k3->parent;
        
        k3->parent = k2;
    }
    if(k2->parent){
        if(k2->parent->right != k2){
            k2->parent->left = k2;
        }
    }
    
    if(c){
        c->parent = k3;
    }
    if(k1->right) {
        k1->right->parent = k1;
    }
    
    return (k1);
    
}


void setBalance(BSTNode* node){
    if(!node){
        return;
    }
    if(node->left){
        node->lHeight = node->left->height;
    }
    else{
        node->lHeight = 0;
    }
    if(node->right){
        node->rHeight = node->right->height;
    }
    else{
        node->rHeight = 0;
    }
    
    node->height = max(node->lHeight, node->rHeight) +1 ;
}




void deleteFixup(char*value, BinarySearchTree *B){
    BSTNode* node = newBSTNode(value);
    node->height = 0;
    while(node != B->root){
        
        if (node->parent && getFavoriteChild(node->parent) == node ) {
            setBalance(node->parent);
            node = node->parent;
        }
        
        else if(getFavoriteChild(node->parent) == 0) {
            setBalance(node->parent);
            return;
        }
        else {
            BSTNode *parent = node->parent;
            BSTNode *sib = sibling(node);
            BSTNode *favoriteChild = getFavoriteChild(sib);
            
            
            if ((favoriteChild && !isLinear(favoriteChild, sib, parent))) {
                
                if(node->left == favoriteChild){
                    rotateLeftRight(node);
                }
                else{
                    rotateRightLeft(node);
                }
                if(!node->parent->parent){
                    B->root = node->parent;
                }
                
                setBalance(node);
                if(sibling(node)){
                    
                }
                
                setBalance(node->parent);
                setBalance(sib);
                setBalance(favoriteChild);
                
                
            } else {
                
                if(node->left == favoriteChild){
                    rotateright(sib);
                    
                }
                else{
                    rotateleft(sib);
                }
                
                if(node->parent==NULL){
                    B->root = node;
                }
                setBalance(parent);
                setBalance(node);
                if(!favoriteChild){
                    return;
                }
                node = favoriteChild;
            }
        }
    }
    
    
}


void deleteAVL(BinarySearchTree *B, char *value){
    deleteFixup(value, B);
}





int isBalanced(BSTNode *node) {
    if (node->lHeight - node->rHeight >= 2 || node->lHeight - node->rHeight <=-2){
        return 0;
    }
    return 1;
}


void insertFixup(BSTNode *node, BinarySearchTree *bst) {
    while ((node != bst->root)) {
        if (node->parent && getFavoriteChild(node->parent) != node ) {
            setBalance(node->parent);
            return;
        }
        
        else if(node->parent && isBalanced(node->parent)) {
            setBalance(node->parent);
            node = node->parent;
        }
        else {
            BSTNode *parent = node->parent;
            BSTNode *favoriteChild = getFavoriteChild(node);
            
            if ((favoriteChild && !isLinear(favoriteChild, node, parent))) {
                
                if(node->left == favoriteChild){
                    rotateLeftRight(node);
                }
                else{
                    rotateRightLeft(node);
                }
                if(!node->parent->parent){
                    bst->root = node->parent;
                }
                
                setBalance(node);
                if(sibling(node)){
                    
                }
                setBalance(favoriteChild);
                setBalance(node->parent);
                
                
            } else {
                
                if(node->left == favoriteChild){
                    rotateright(node);
                    
                }
                else{
                    rotateleft(node);
                }
                
                if(node->parent==NULL){
                    bst->root = node;
                }
                setBalance(parent);
                setBalance(node);
            }
            
            return;
        }
    }
    
    
}



void insertNodeAVL(char *value, BinarySearchTree *tree, int *duplicate){
    BSTNode *node = insertNode(value, tree, duplicate);
    if(node != NULL){
        insertFixup(node, tree);
    }
}

BSTNode *insertNode(char *value, BinarySearchTree *tree, int *duplicate) {
    BSTNode *root = tree->root;
    BSTNode* currentNode = root;
    BSTNode* parentNodev = 0;
    if(root == 0) {
        root = newBSTNode(value);
    } else {
        int isLeft  = 0;
        
        while(currentNode != 0) {
            parentNodev = currentNode;
            if (strcmp(value, currentNode->value) < 0) {
                isLeft = 1;
                currentNode = currentNode->left;
            } else if (strcmp(value, currentNode->value) > 0) {
                isLeft = 0;
                currentNode = currentNode->right;
            } else {
                currentNode->value = value;
                currentNode->freq++;
                *duplicate = 1;
                return NULL;
                
            }
            
        }
        if(isLeft) {
            parentNodev->left = newBSTNode(value);
            parentNodev->left->parent = parentNodev;
            setBalance(parentNodev);
            if(parentNodev->parent){
                setBalance(parentNodev->parent);
            }
            
            return parentNodev->left;
        } else {
            parentNodev->right = newBSTNode(value);
            parentNodev->right->parent = parentNodev;
            setBalance(parentNodev);
            if(parentNodev->parent){
                setBalance(parentNodev->parent);
            }
            
            return parentNodev->right;
        }
        
    }
    tree->root = root;
    if(!parentNodev){
        return root;
    }
    
    return parentNodev;
}

BSTNode *recursiveDelete(char *value, BSTNode *root) {
    if(root == 0) {
        return 0;
    }
    
    BSTNode *currentNode;
    if(strcmp(value, root->value) < 0) {
        root->left = recursiveDelete(value, root->left);
    } else if(strcmp(value, root->value) > 0) {
        root->right = recursiveDelete(value, root->right);
    } else {
        
        if(root->freq > 1)
        {
            root->freq--;
        }
        
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

void deleteNode(char *value, BinarySearchTree *tree) {
    tree->root = recursiveDelete(value, tree->root);
}


BSTNode* searchTree(char *value, BinarySearchTree *tree) {
    BSTNode *root = tree->root;
    
    if(root == 0) {
        return 0;
    }
    
    BSTNode* currentNode = root;
    while(currentNode != 0 && currentNode->value != 0) {
        if (strcmp(value, currentNode->value) < 0) {
            currentNode = currentNode->left;
        } else if (strcmp(value, currentNode->value) > 0) {
            currentNode = currentNode->right;
        }else {
            return currentNode;
        }
        
    }
    return currentNode;
}



int recursivePrint(BSTNode *node, int level, Queue *Q ) {
    int i = 0;
    if (node == 0) {
        return 0;
    }
    if (level == 1)
    {
        enqueue(node, Q);
        i++;
    }
    else
    {
        recursivePrint(node->left, level - 1, Q);
        recursivePrint(node->right, level - 1, Q);
    }
    return i;
}



Queue* buildQueue(BinarySearchTree *tree, int avlFlag) {
    int treeHeight = 0;;
    if (!avlFlag){
        treeHeight = height(tree->root);
    }
    else{
        treeHeight = tree->root->height;
    }
    Queue *Q = newQueue();
    int i = 0;
    for(i=1; i<= treeHeight; ++i)
    {
        recursivePrint(tree->root, i, Q);
        enqueue(NULL, Q);
    }
    
    
    return Q;
    
}
