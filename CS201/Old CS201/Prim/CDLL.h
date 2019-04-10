#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "vertex.h"
#ifndef CDLL_h
#define CDLL_h


struct node
{
    int data;
    int size;
    int degree;
    int weight;
    void *value;
    struct node *next, *prev, *parent, *children;
    struct vertex *vertex;
};


struct node *split(struct node *head);
#endif


struct node *merge(struct node *first, struct node *second);

void insert(struct node **head, struct node* data);
struct node *deleteNode(struct node **head, struct node **del);
void print(struct node *head);
struct node * makeCDLL();
struct node * newNode(struct vertex *value);
struct node *mergeSort(struct node *head);