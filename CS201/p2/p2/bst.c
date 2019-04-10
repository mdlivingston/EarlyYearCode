#include "bst.h"
#include "queue.h"
#include <stdlib.h>

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    bst *bintree = malloc(sizeof(*bintree));
    bintree->root = 0;
    bintree->display = d;
    bintree->compare = c;
    bintree->size = 0;
    return bintree;
}

bstNode *newBSTNode(void *value) {
    bstNode *bstNod = malloc(sizeof(*bstNod));
    bstNod->value = value;
    bstNod->left = 0;
    bstNod->right = 0;
    bstNod->parent = 0;
    return bstNod;
}

bstNode *findBSTNode(bst *tree,void *value){
    bstNode *root = tree->root;
    if(root == NULL) {
        return 0;
    }
    bstNode *currentNode = root;
    while(currentNode != 0 && currentNode->value != 0) {
        if (tree->compare(value, currentNode->value) < 0) {
            currentNode = currentNode->left;
        } else if (tree->compare(value, currentNode->value) > 0) {
            currentNode = currentNode->right;
        }else {
            return currentNode;
        }
    }
    return currentNode;
}

int shortestPath(bst *tree){
    queue *Q = newQueue(tree->display);
    enqueue(Q, tree->root);
    enqueue(Q, NULL);
    int counter = 0;
    if(!tree->root){
        return counter;
    }
    while(Q){
        bstNode *node = dequeue(Q);
        if(sizeQueue(Q) == 0){
            return counter + 1;
        }
        if(!node){
            counter++;
            enqueue(Q, NULL);
        }
        else{
            if(!node->left || !node->right){
                return counter + 1 ;
            }
            if (node->left){
                enqueue(Q, node->left);
            }
            if(node->right){
                enqueue(Q, node->right);
            }
        }
    }
    return counter;
}

int longestPath(bst *tree){
    queue *Q = newQueue(tree->display);
    enqueue(Q, tree->root);
    enqueue(Q, NULL);
    int counter2 = 0;
    if(!tree->root){
        return counter2;
    }
    while(Q){
        bstNode *node = dequeue(Q);
        if(sizeQueue(Q) == 0){
            return counter2 + 1;
        }
        
        if(node == NULL){
            counter2++;
            enqueue(Q, NULL);
        }
        else{
            if (node->left){
                enqueue(Q, node->left);
            }
            if(node->right){
                enqueue(Q, node->right);
            }
        }
    }
    return counter2;
}

int findBST(bst *tree,void *value){
    bstNode *node = findBSTNode(tree, value);
    if(node){
        return 1;
    }
    else{
        return 0;
    }
}

bstNode *insertNode(bstNode*val, bst*tree){
    bstNode *value = val;
    int isLeft  = 0;
    bstNode* currentNode = tree->root;
    bstNode* parentNodev = 0;
    while(currentNode){
        parentNodev = currentNode;
        if (tree->compare(value->value,currentNode->value) < 0) {
            isLeft = 1;
            currentNode = currentNode->left;
        } else if(tree->compare(value->value,currentNode->value) > 0) {
            isLeft = 0;
            currentNode = currentNode->right;
        }
        else{
            tree->size--;
            return value;
        }
    }
    if(isLeft) {
        parentNodev->left = value;
        value->parent = parentNodev;
    } else {
        parentNodev->right = value;
        value->parent = parentNodev;
    }
    return value;
    
}
bstNode *insertBST(bst *tree,void *val){
    bstNode *value = newBSTNode(val);
    tree->size++;
    if(!tree->root) {
        tree->root = value ;
        tree->root->parent = value;
        return value;
    }
    else {
        return insertNode(value, tree);
    }
}
bstNode *swapToLeafBSTNode(bstNode *node){
    bstNode *temp = node;
    if(!node || (node->left == NULL && node->right == NULL)){
        return node;
    }
    else if(!temp->left){
        temp = node->right;
        while(temp->left){
            temp = temp->left;
        }
    }
    else{
        temp = temp->left;
        while(temp->right){
            temp = temp->right;
        }
    }
    void* temp2 = temp->value;
    temp->value = node->value;
    node->value = temp2;
    
    return swapToLeafBSTNode(temp);
}

void displayBST(FILE *fp, bst*tree){
    queue *Q = 0;
    int lineNum = 0;
    if(tree->root){
        fprintf(fp,"%d:",lineNum);
        Q = newQueue(NULL);
        enqueue(Q, tree->root);
        enqueue(Q, NULL);
    }
    else{
        fprintf(fp,"%d:\n",lineNum);
        return;
    }
    while(sizeQueue(Q) > 0){
        bstNode *node = dequeue(Q);
        if(sizeQueue(Q) == 0){
            fprintf(fp,"\n");
            break;
        }
        if(!node){
            fprintf(fp,"\n");
            lineNum++;
            fprintf(fp,"%d:",lineNum);
            enqueue(Q, NULL);
        }
        else{
            fprintf(fp," ");
            if(!node->left && !node->right){
                fprintf(fp,"=");
            }
            tree->display(fp,node->value);
            fprintf(fp,"(");
            tree->display(fp,node->parent->value);
            fprintf(fp,")");
            if(node == tree->root){
                fprintf(fp,"-");
            }
            else if(node->parent->left == node){
                fprintf(fp,"-l");
            }
            else{
                fprintf(fp,"-r");
            }
            if (node->left){
                enqueue(Q, node->left);
            }
            if(node->right){
                enqueue(Q, node->right);
            }
        }
    }
}

void statisticsBST(bst *tree,FILE *fp){
    fprintf(fp,"Nodes: %d\n", tree->size);
    fprintf(fp,"Minimum depth: %d\n", shortestPath(tree));
    fprintf(fp,"Maximum depth: %d\n", longestPath(tree));
}

int sizeBST(bst *tree){
    return tree->size;
}

void pruneBSTNode(bst *tree, bstNode *node){
    if(node){
        tree->size--;
        if(node->parent != node) {
            if(node->parent->right == node){
                node->parent->right = NULL;
            }
            else{
                node->parent->left = NULL;
            }
        }
        else{
            tree->root = NULL;
            tree = NULL;
        }
    }
}
