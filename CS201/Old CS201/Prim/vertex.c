//
//  vertex.c
//  Prim
//
//  Created by Max Livingston on 11/26/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//

#include "vertex.h"

struct vertex *newVertexNode(int value, double weight){
    struct vertex *node = malloc(sizeof(*node));
    node->key = weight;
    node->data = value;
    node->predecessor = NULL;
    node->owner = NULL;
    node->heapFlag = 0;
    return node;
}

int comparator(void* a, void*b){
    struct vertex* x = ((struct vertex *)a);
    struct vertex* y = ((struct vertex *)b);
    double result = x->key - y->key ;
    if(result == 0){
        if(result == 0){
            if(!x->predecessor && !y->predecessor){
                result = 0;
            }
            else{
                result = x->predecessor->data - y->predecessor->data;
            }
            if(result == 0){
                result = x->data - y->data;
            }
        }
        
    }
    return result;
}
