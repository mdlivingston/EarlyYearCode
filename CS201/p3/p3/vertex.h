//
//  vertex.h
//  Prim
//
//  Created by Max Livingston on 11/26/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//

#ifndef vertex_h
#define vertex_h

#include <stdio.h>
#include "darray.h"
#include "integer.h"
#include "binomial.h"

typedef struct vertex
{
    int key;
    int value;
    int visited;
    int pred;
    BinomialNode *node;
    DArray *neighbors;
} vertex;

#endif /* vertex_h */

vertex *newVertexNode(integer *value,void (*display)(FILE *,void *));
void updateVertex(void *v1, BinomialNode *v2);
int compareVertex(void *v,void *w);
void displayVertexValue(FILE *fp,void *v);
void displayVertexWeight(FILE *fp,void *v);
int getVertexWeight(vertex *v);
int getVertexNum(vertex *v);
