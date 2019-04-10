//
//  rbt.c
//  p2
//
//  Created by Max Livingston on 3/5/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

#include "rbt.h"
#include "string.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>

typedef struct rbtValue
{
    void *value;
    int frequency;
    int color;
    void (*display)(FILE*,void*);
    int (*compare)(void*,void*);
}rbtValue;

rbtValue *newRBTValue(void*value,void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbtValue *rbtVal = malloc(sizeof(rbtValue));
    rbtVal->value = value;
    rbtVal->compare = c;
    rbtVal->display = d;
    rbtVal->frequency = 1;
    rbtVal->color = 1;
    return rbtVal;
}

int rbtComparator(void *v,void *w)
{
    rbtValue *temp = v;
    rbtValue *temp2 = w;
    return temp->compare(temp->value,temp2->value);
}

void displayRBTValue(FILE*fp,void*value){
    rbtValue *val = value;
    val->display(fp, val->value);
    if(val->frequency>1){
        fprintf(fp,"-%d",val->frequency);
    }
    if(val->color == 0){
        fprintf(fp,"-B");
    }
    else{
        fprintf(fp,"-R");
    }
}

extern rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)){
    rbt *rBT = malloc(sizeof(rbt));
    rBT->tree = newBST(displayRBTValue,rbtComparator);
    rBT->size = 0;
    rBT->words = 0;
    rBT->display = d;
    rBT->compare = c;
    return rBT;
}

int color(rbtValue *value){
    if(value == NULL){
        return 0;
    }
    else{
        return value->color;
    }
}

int isLinear(bstNode *favoriteChild, bstNode *node, bstNode *parent, bst *tree) {
    if(parent){
        if ((favoriteChild == node->left && node == parent->left) || (favoriteChild == node->right && node == parent->right)) {
            return 1;
        }
    }
    if(!parent || node == tree->root){
        return 1;
    }
    return 0;
}


bstNode *isLeftChild(bstNode *parent, bstNode *grandparent){
    if(grandparent->left == parent){
        return grandparent;
    }
    else{
        return  NULL;
    }
}
void leftRotate(bstNode *node, bstNode *root,rbt *tree){
    bstNode *nodeLeft = node->left;
    bstNode *parent = node->parent;
    
    node->left = parent;
    parent->right = nodeLeft;
    
    if (nodeLeft) {
        nodeLeft->parent = parent;
    }
    if (parent == root) {
        tree->tree->root = node;
        node->parent = node;
    } else {
        node->parent = parent->parent;
        if (isLeftChild(parent, parent->parent)) {
            parent->parent->left = node;
        } else {
            parent->parent->right = node;
        }
    }
    
    parent->parent = node;
}

void rightRotate(bstNode *node, bstNode *root,rbt *tree) {
    bstNode *nodeRight = node->right;
    bstNode *parent = node->parent;
    node->right = parent;
    parent->left = nodeRight;
    
    if (nodeRight) {
        nodeRight->parent = parent;
    }
    if (parent == root) {
        tree->tree->root = node;
        node->parent = node;
    } else {
        node->parent = parent->parent;
        if (isLeftChild(parent, parent->parent)) {
            parent->parent->left = node;
        } else {
            parent->parent->right = node;
        }
    }
    
    parent->parent = node;
}

bstNode *grandFather(bstNode *node){
    if(node->parent){
        if(node->parent->parent){
            return node->parent->parent;
        }
    }
    return NULL;
}
bstNode *uncle(bstNode *node){
    bstNode *grandDaddy = grandFather(node);
    if(grandDaddy&& grandDaddy != node->parent){
        if(isLeftChild(node->parent, grandDaddy)){
            return grandDaddy->right;
        }
        else{
            return grandDaddy->left;
        }
        
    }
    return NULL;
}

extern void insertRBT(rbt *tree,void *value){
    bst *bstTree = tree->tree;
    rbtValue *val = newRBTValue(value, tree->display, tree->compare);
    bstNode *inNode = 0;
    bstNode *foundNode = findBSTNode(bstTree, val);
    tree->words++;
    if(foundNode){
        val = foundNode->value;
        val->frequency++;
    }
    else{
        tree->size++;
        inNode = insertBST(bstTree, val);
        while(1){
            if (inNode == tree->tree->root){
                break;
            }
            if(color(inNode->parent->value) == 0){
                break;
            }
            if(uncle(inNode) && color(uncle(inNode)->value)==1){
                bstNode *parent = inNode->parent;
                rbtValue *parentVal = parent->value;
                parentVal->color = 0;
                bstNode *unclee = uncle(inNode);
                rbtValue *uncleVal = unclee->value;
                uncleVal->color = 0;
                bstNode *grandparent =  grandFather(inNode);
                rbtValue *grandparVal = grandparent->value;
                grandparVal->color = 1;
                inNode = grandparent;
            }
            else{
                if(!isLinear(inNode, inNode->parent, grandFather(inNode),bstTree)){
                    bstNode *oldParent = inNode->parent;
                    bstNode *oldNode = inNode;
                    if(isLeftChild(inNode, inNode->parent)){
                        rightRotate(inNode, tree->tree->root,tree);
                    }
                    else{
                        leftRotate(inNode, tree->tree->root,tree);
                    }
                    inNode = oldParent;
                    inNode->parent = oldNode;
                }
                bstNode *parent = inNode->parent;
                rbtValue *parentVal = parent->value;
                parentVal->color = 0;
                bstNode *grandparent =  grandFather(inNode);
                if(grandparent &&parent != grandparent){
                    rbtValue *grandparVal = grandparent->value;
                    grandparVal->color = 1;
                    if(grandparent->right == parent){
                        leftRotate(parent, tree->tree->root,tree);
                    }
                    else{
                        rightRotate(parent, tree->tree->root,tree);
                    }
                }
                break;
            }
        }
        rbtValue *rootValue = tree->tree->root->value;
        rootValue->color = 0;
    }
}
extern int findRBT(rbt *tree,void *value){
    rbtValue *newNode = newRBTValue(value, tree->display, tree->compare);
    bstNode *showNode = findBSTNode(tree->tree, newNode);
    if (showNode){
        rbtValue *freqNode = showNode->value;
        return freqNode->frequency;
    }
    else{
        return 0;
    }
}
extern void deleteRBT(rbt *tree,void *value){
    // RBT delete is not functional
        fprintf(stderr, "Value ");
        tree->display(stderr, value);
        fprintf(stderr, " cannot be deleted.\n");

}
extern int sizeRBT(rbt *tree){
    return tree->size;
}
extern int wordsRBT(rbt *tree){
    return tree->words;
}
extern void statisticsRBT(rbt *tree,FILE *fp){
    fprintf(fp,"Words/Phrases: %d\n", tree->words);
    statisticsBST(tree->tree, fp);
}
extern void displayRBT(FILE *fp, rbt *tree){
    displayBST(fp, tree->tree);
}
