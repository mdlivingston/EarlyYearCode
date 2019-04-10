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
#include "CDLL.h"
struct vertex
{
    double key;
    int data;
    int heapFlag;
    int seen;
    struct node *predecessor;
    struct node *owner;
    struct vertex* next;
};

#endif /* vertex_h */

struct vertex *newVertexNode(int value, double weight);
int comparator(void* a, void*b);