////
////  binheap.c
////  Prim
////
////  Created by Max Livingston on 11/15/16.
////  Copyright © 2016 Max Livingston. All rights reserved.
////
//
#include "binheap.h"
#include "stdlib.h"
#include "math.h"


Binheap *newBinHeap(int (*comparator)(void *, void*)){
    Binheap *b = malloc(sizeof b);
    b->comparator = comparator;
    b->extreme = NULL;
    b->rootlist = makeCDLL();
    b->size = 0;
    return b;
    
}

struct node *combine(Binheap *b, struct node *x, struct node *y){
    if(b->comparator(x->vertex,y->vertex) == 0){
        return x;
    }
    else if ( b->comparator(x->vertex,y->vertex) < 0){
        x->children = merge(x->children, y);
        y->parent = x;
        x->size++;
        return x;
    }
    else
    {
        y->children = merge(y->children, x);
        x->parent = y;
        y->size++;
        return y;
    }
}


void updateConsolidate(struct node **D, struct node *spot, Binheap *b){
    int degree = spot->degree;
    
    
    while(D && D[degree]){
        spot = combine(b,  spot, D[degree]);
        D[degree] = NULL;
        degree++;
        spot->degree++;
    }
    D[degree] = spot;
}

void consolidate(Binheap *b){
    int bSizeOrig = b->size;
    struct node **D;
    int Dsize = (int)log2(b->size)+1;
    D = calloc(sizeof(struct node *) * Dsize, sizeof(b->size));
    
    while(b->rootlist != NULL){
        struct node *spot = b->rootlist;
        spot->prev = NULL;
        deleteNode(&b->rootlist, &spot);
        b->size--;
        if(b->size == 0){
            b->rootlist = NULL;
        }
        updateConsolidate(D, spot, b);
        
    }
    b->extreme = NULL;
    for(int i= 0; i< Dsize ; ++i){
        if (D[i] != NULL){
            insert(&b->rootlist, D[i]);
            b->size = bSizeOrig;
            b->rootlist->size--;
            if(!b->extreme || b->comparator(b->extreme->vertex, D[i]->vertex) > 0){
                b->extreme = D[i];
            }
        }
    }
    free(D);
    
}


struct node *findNode(struct node *b, int value){
    struct node *temp = b;
    struct vertex *v = newVertexNode(-5, 0);
    struct node *temp2 = newNode(v);
    
    if(temp->data == value){
        temp2 = temp;
        return temp2;
    }
       if(temp->children != NULL && temp2->next == NULL && temp2->prev == NULL){
        *temp2 = *findNode(temp->children, value);
    }
    if(temp->next != NULL && temp2->next == NULL && temp2->prev == NULL){
        *temp2 = *findNode(temp->next, value);
    }

   
    
    
    
    return temp2;
}
struct node *bubbleUp(Binheap *b, struct node *n){
    if(n->data == n->parent->data){
        return n;
    }
    else if (b->comparator(n->vertex,n->parent->vertex) >= 0){
        return n;
    }
    else{
        int temp;
        struct node *owner = n->parent->vertex->owner;
        
        n->parent->vertex->owner = n->vertex->owner;
        n->vertex->owner = owner;
        struct node *parent = n->parent;
        
        temp = n->data;
        
        n->data = parent->data;
        
        parent->data = temp;
        
        struct node *child;
        
        child = findNode(parent->children, temp);
        child->data = n->data;
        if(child->children){
            n->children->parent->data = n->data;
            n->children->parent->vertex = parent->vertex;
            n = child;
            
        }
        struct vertex *swap = n->vertex;
        
        n->vertex = parent->vertex;
        
        parent->vertex = swap;
        child->vertex = n->vertex;
        
        return bubbleUp(b, n->parent);
    }
}

struct node *insertBin(Binheap *b, void* v){
    struct node *newLL = makeCDLL();
    struct vertex *vert = (struct vertex*) v;
    struct node *n = newNode(vert);
    n->vertex->owner = n;
    n->parent = n;
    n->children = newLL;
    insert(&b->rootlist, n);
    b->size++;
    if(b->size > 1){
        consolidate(b);
    }
    else{
        b->extreme = b->rootlist;
    }
    return n;
    
}

struct node *extractMin(Binheap *b){
    struct node *y = b->extreme;
    struct node *temp = y->children;
    deleteNode(&b->rootlist, &y);
    y->vertex->heapFlag = 1;
    while(temp != NULL){
        temp->parent = temp;
        temp = temp->next;
        
    }
    if(!b->rootlist){
        b->rootlist = y->children;
    }
    else{
        if(y->children){
            b->rootlist =  merge(b->rootlist,y->children);
        }
        
    }
    
    consolidate(b);
    b->rootlist =  mergeSort(b->rootlist);
    b->size--;
    return y;
    
}
int isInMinHeap(int u, int v)
{
    if (v > u)
        return 1;
    return 0;
}
void decreaseKey(Binheap *b, struct node *n, double newvalue){
    n->vertex->key = newvalue;
    struct node *ex = bubbleUp(b, n);
        if(b->comparator(b->extreme->vertex, ex->vertex) > 0){
        b->extreme = ex;
        }
}

