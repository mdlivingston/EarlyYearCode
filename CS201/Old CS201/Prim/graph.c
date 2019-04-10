//
//  graph.c
//  Prim
//
//  Created by Max Livingston on 11/28/16.
//  Copyright © 2016 Max Livingston. All rights reserved.
//

#include "graph.h"


struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i){
        graph->array[i].head = NULL;
        graph->array[i].startV = newVertexNode(i, INT_MAX);
    }
    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct vertex *newVertex = newVertexNode(dest, weight);
    struct node *newNodee = newNode(newVertex);
    newNodee->next = graph->array[src].head;
    graph->array[src].head = newNodee;
    
    // Since graph is undirected, add an edge from dest to src also
    struct vertex *newVertex2 = newVertexNode(src, weight);
    struct node *newNodee2 = newNode(newVertex2);
    newNodee2->next = graph->array[dest].head;
    graph->array[dest].head = newNodee2;
    
    
    
}
