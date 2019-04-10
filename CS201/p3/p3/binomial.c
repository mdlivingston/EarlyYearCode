//
//  binomial.c
//  p3
//
//  Created by Max Livingston on 3/21/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

#include "binomial.h"
#include <stdlib.h>
#include "queue.h"

struct BinomialNode{
    void *value;
    DArray *children;
    BinomialNode *parent;
    void (*display)(FILE *,void *);
};

BinomialNode *newBinomialNode(void (*d)(FILE *,void *),void *val){
    BinomialNode *binNode = malloc(sizeof *binNode);
    binNode->value = val;
    binNode->children = NULL;
    binNode->parent = NULL;
    binNode->display = d;
    return binNode;
}
struct Binomial{
    DArray *rootlist;
    int (*compare)(void *,void *);
    void (*update)(void *,BinomialNode *);
    BinomialNode *extreme;
    int size;
    void (*display)(FILE *,void *);
};

extern Binomial *newBinomial(void (*d)(FILE *,void *),int (*c)(void *,void *),void (*u)(void *,BinomialNode *)){
    Binomial *binHeap = malloc(sizeof * binHeap);
    binHeap->rootlist = newDArray(d);
    binHeap->display = d;
    binHeap->compare = c;
    binHeap->update = u;
    binHeap->size = 0;
    binHeap->extreme = NULL;
    return binHeap;
}

void displayBinomialNode(FILE *fp,BinomialNode *n){
    n->display(fp,n->value);
}
void setExtreme(Binomial*b){
    if(sizeBinomial(b) == 1){
        b->extreme = getDArray(b->rootlist, 0);
    }
    else{
        for(int i = 0; i < sizeDArray(b->rootlist); i++){
            if(getDArray(b->rootlist, i)){
                BinomialNode* node = getDArray(b->rootlist, i);
                if(b->extreme){
                    if(b->compare(node->value,b->extreme->value) < 0){
                        b->extreme = node;
                    }
                }
                else{
                    b->extreme = node;
                }
            }
        }
    }
}
BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y){
    if(b->compare(x->value,y->value) < 0){
        int i = sizeDArray(y->children);
        setDArray(x->children, i, y);
        y->parent = x;
        return x;
    }
    else{
        int i = sizeDArray(x->children);
        setDArray(y->children, i, x);
        x->parent = y;
        return y;
    }
}

void consolidate(Binomial *b, BinomialNode *n){
    int degree = sizeDArray(n->children);
    while(degree < sizeDArray(b->rootlist) && getDArray(b->rootlist, degree)){
        n = combine(b, getDArray(b->rootlist, degree), n);
        setDArray(b->rootlist, degree, NULL);
        degree++;
    }
    setDArray(b->rootlist, degree, n);
}
void mergeDArray(Binomial *b, DArray *donor){
    for(int i = 0; i < sizeDArray(donor); i++){
        BinomialNode *node = getDArray(donor, i);
        if(node){
            node->parent = node;
            consolidate(b, node);
        }
    }
    free(donor);
}

extern BinomialNode *insertBinomial(Binomial *b,void *value){
    BinomialNode *n = newBinomialNode(b->display, value);
    n->parent = n;
    n->children = newDArray(n->display);
    consolidate(b, n);
    b->size++;
    setExtreme(b);
    return n;
}
extern int sizeBinomial(Binomial *b){
    return b->size;
}

BinomialNode *bubbleUp(Binomial *b, BinomialNode *n){
    if(n == n->parent){
        return n;
    }
    else if(b->compare(n->value,n->parent->value) >= 0){
        return n;
    }
    else{
        b->update(n->value,n->parent);
        b->update(n->parent->value, n);
        void *swapper = n->value;
        n->value = n->parent->value;
        n->parent->value = swapper;
        return bubbleUp(b, n->parent);
    }
}
extern void deleteBinomial(Binomial *b,BinomialNode *n){
    decreaseKeyBinomial(b, n, NULL);
    extractBinomial(b);
}
extern void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value){
    n->value = value;
    BinomialNode *ex = bubbleUp(b, n);
    if(b->compare(b->extreme->value,ex->value) > 0){
        b->extreme = ex;
    }
}
extern void *extractBinomial(Binomial *b){
    BinomialNode *y = b->extreme;
    setDArray(b->rootlist, sizeDArray(y->children), NULL);
    mergeDArray(b, y->children);
    b->size--;
    void *value = y->value;
    free(b->extreme);
    b->extreme = NULL;
    setExtreme(b);
    return value;
}
extern void displayBinomial(FILE *fp,Binomial *b){
    if(sizeBinomial(b) == 0){
        return;
    }
    for (int i = 0; i< sizeDArray(b->rootlist); i++){
        BinomialNode *roots = getDArray(b->rootlist, i);
        if(roots){
            queue *Q = newQueue(b->display);
            int lineNum = 0;
            int indexCrawl = 0;
            if(roots){
                fprintf(fp,"%d:",lineNum);
                Q = newQueue(NULL);
                enqueue(Q, roots);
                enqueue(Q, NULL);
            }
            else{
                fprintf(fp,"%d:\n",lineNum);
                return;
            }
            while(sizeQueue(Q) > 0){
                BinomialNode *node = dequeue(Q);
                if(sizeQueue(Q) == 0){
                    fprintf(fp,"\n----\n");
                    break;
                }
                if(!node){
                    fprintf(fp,"\n");
                    lineNum++;
                    indexCrawl =0;
                    fprintf(fp,"%d:",lineNum);
                    enqueue(Q, NULL);
                }
                else{
                    fprintf(fp," ");
                    displayBinomialNode(fp, node);
                    fprintf(fp, "-%d", sizeDArray(node->children));
                    if(node->parent != node){
                        fprintf(fp,"(");
                        displayBinomialNode(fp, node->parent);
                        fprintf(fp, "-%d", sizeDArray(node->parent->children));
                        fprintf(fp,")");
                    }
                    BinomialNode *check = getDArray(node->children, indexCrawl);
                    if(check){
                        for(int i = 0; i < sizeDArray(node->children); i++){
                            check = getDArray(node->children, i);
                            enqueue(Q, check);
                        }
                    }
                }
            }
        }
    }
}
