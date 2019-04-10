//
//  vertex.c
//  Prim
//
//  Created by Max Livingston on 11/26/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//

#include "vertex.h"
#include <stdlib.h>
#include <limits.h>

vertex *newVertexNode(integer *val,void (*display)(FILE *,void *)){
    vertex *node = malloc(sizeof(*node));
    node->key = 0;
    node->value= val->value;
    node->visited = 0;
    node->neighbors = newDArray(display);
    node->node = NULL;
    node->pred = 0;
    return node;
}

int getVertexNum(vertex *v){
    if(!v){
        return '\0';
    }
    return v->value;
}

int getVertexWeight(vertex *v){
    if(!v){
        return '\0';
    }
    return v->key;
}

void updateVertex(void *v1, BinomialNode *v2){
    vertex *vert1 = v1;
    vert1->node = v2;
}
int compareVertex(void *v,void *w)
{
    vertex *num1 = v;
    vertex *num2 = w;
    if(num1 == NULL){
        return 1;
    }
    if(num2 == NULL){
        return -1;
    }
    if(num1->key != num2->key){
        return num1->key - num2->key;
    }
    return num1->value - num2->value;
}

void displayVertexValue(FILE *fp,void *v){
    fprintf(fp,"%d",getVertexNum(v));
}

void displayVertexWeight(FILE *fp,void *v){
    fprintf(fp,"%d",getVertexWeight(v));
}
