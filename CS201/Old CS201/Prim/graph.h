//
//  graph.h
//  Prim
//
//  Created by Max Livingston on 11/28/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>
#include "CDLL.h"
#include "binheap.h"
// A structure to represent a node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct node* next;
};

// A structure to represent an adjacency liat
struct AdjList
{
    struct node *head;  // pointer to head node of list
    struct vertex* startV;
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
    struct vertex* head;
    
};

// A utility function to create a new adjacency list node

#endif /* graph_h */

struct AdjListNode* newAdjListNode(int dest, int weight);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);