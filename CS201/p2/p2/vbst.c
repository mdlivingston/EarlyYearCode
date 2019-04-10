//
//  vbst.c
//  p2
//
//  Created by Max Livingston on 3/5/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

#include "vbst.h"
#include "string.h"
#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct vbstValue
{
    void *value;
    int frequency;
    void (*display)(FILE*,void*);
    int (*compare)(void*,void*);
}vbstValue;

vbstValue *newVBSTValue(void*value,void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    vbstValue *vbstVal = malloc(sizeof(vbstValue));
    vbstVal->value = value;
    vbstVal->compare = c;
    vbstVal->display = d;
    vbstVal->frequency = 1;
    return vbstVal;
}

int vbstComparator(void *v,void *w)
{
    vbstValue *temp = v;
    vbstValue *temp2 = w;
    
    return temp->compare(temp->value,temp2->value);
}

void displayVBSTValue(FILE*fp,void*value){
    vbstValue *val = value;
    val->display(fp, val->value);
    if(val->frequency>1){
        fprintf(fp,"-%d",val->frequency);
    }
}

vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *)){
    vbst *vBST = malloc(sizeof(vbst));
    vBST->tree = newBST(displayVBSTValue, vbstComparator);
    vBST->size = 0;
    vBST->words = 0;
    vBST->display = d;
    vBST->compare = c;
    return vBST;
}

void insertVBST(vbst *tree,void *value){
    bst *bstTree = tree->tree;
    vbstValue *val = newVBSTValue(value, tree->display, tree->compare);
    bstNode *foundNode = findBSTNode(bstTree, val);
    if(foundNode){
        val = foundNode->value;
        val->frequency++;
    }
    else{
        tree->size++;
        insertBST(bstTree, val);
    }
    tree->words++;
}

int findVBST(vbst *tree,void *value){
    vbstValue *newNode = newVBSTValue(value, tree->display, tree->compare);
    bstNode *showNode = findBSTNode(tree->tree, newNode);
    if (showNode){
        vbstValue *freqNode = showNode->value;
        return freqNode->frequency;
    }
    else{
        return 0;
    }
}

void deleteVBST(vbst *tree,void *value){
    vbstValue *val = newVBSTValue(value, tree->display, tree->compare);
    bstNode *node = findBSTNode(tree->tree, val);
    if(node != NULL){
        val = node->value;
        if(val->frequency>1){
            val->frequency--;
        }
        else{
            bstNode *deadMan = swapToLeafBSTNode(node);
            pruneBSTNode(tree->tree, deadMan);
            tree->size--;
        }
        tree->words--;
    }
    else{
        fprintf(stderr, "Value ");
        tree->display(stderr, value);
        fprintf(stderr, " not found.\n");
    }
    
}
extern int sizeVBST(vbst *tree){
    return tree->size;
}
extern int wordsVBST(vbst *tree){
    return tree->words;
}
extern void statisticsVBST(vbst *tree,FILE *fp){
    fprintf(fp,"Words/Phrases: %d\n", tree->words);
    statisticsBST(tree->tree, fp);
}
extern void displayVBST(FILE *fp, vbst *tree){
    displayBST(fp, tree->tree);
}
