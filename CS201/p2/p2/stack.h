
#ifndef stack_h
#define stack_h

#include <stdio.h>
#include "dll.h"

typedef struct STACK{
    dll *stack;
} stack;

stack *newStack(void (*d)(FILE *,void *));   //constructor
extern void push(stack *items, void *value);                     //stores a generic value
extern void *pop(stack *items);                     //returns a generic value
extern void *peekStack(stack *items);               //returns a generic value
extern void displayStack(FILE *,stack *items);
extern int sizeStack(stack *items);
#endif /* stack_h */
