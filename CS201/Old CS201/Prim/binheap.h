//
//  binheap.h
//  Prim
//
//  Created by Max Livingston on 11/15/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//
#include <stdio.h>
#include "CDLL.h"
#include "vertex.h"
#ifndef binheap_h
#define binheap_h

typedef struct {
    int size;
    int (*comparator)(void*, void*);
    struct node *rootlist;
    struct node *extreme;
    
} Binheap;

#endif /* binheap_h */

struct node *insertBin(Binheap *b, void* v);
Binheap *newBinHeap(int (*comparator)(void *, void*));
int comparator(void* a, void*b);
void  decreaseKey(Binheap *b, struct node *n, double newvalue);
struct node *extractMin(Binheap *b);
int isInMinHeap(int u, int v);
struct node *findNode(struct node *b, int value);
struct node *gotNode(struct node *b, int value);