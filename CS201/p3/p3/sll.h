
#ifndef sll_h
#define sll_h
#include <stdio.h>
#include <stdlib.h>


typedef struct sllnode
{
    void *value;
    struct sllnode *next;
    
} sllnode;

extern sllnode *newSLLNODE(void *);

typedef struct sll
{
    sllnode *head;
    sllnode *tail;
    int size;
    void (*display)(FILE *,void *);
} sll;

extern sll *newSLL(void (*d)(FILE *,void *));            //constructor
extern void insertSLL(sll *items,int index,void *value); //stores a generic value
extern void *removeSLL(sll *items,int index);            //returns a generic value
extern void unionSLL(sll *recipient,sll *donor);         //merge two lists into one
extern int sizeSLL(sll *items);
extern void displaySLL(FILE *,sll *items);
extern void *getSLL(sll *items, int index);

#endif
