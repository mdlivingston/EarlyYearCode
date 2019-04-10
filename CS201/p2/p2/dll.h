
#ifndef dll_h
#define dll_h
#include <stdio.h>
#include <stdlib.h>
#include "sll.h"


typedef struct dllnode
{
    void *value;
    struct dllnode *next;
    struct dllnode *prev;
} dllnode;

extern dllnode *newDLLNODE(void *);

typedef struct dll
{
    dllnode *head;
    dllnode *tail;
    int size;
    void (*display)(FILE *,void *);
} dll;

extern dll *newDLL(void (*d)(FILE *,void *));            //constructor
extern void insertDLL(dll *items,int index,void *value); //stores a generic value
extern void *removeDLL(dll *items,int index);            //returns a generic value
extern void unionDLL(dll *recipient,dll *donor);         //merge two lists into one
extern int sizeDLL(dll *items);
extern void displayDLL(FILE *,dll *items);
extern void *getDLL(dll *items, int index);
#endif
