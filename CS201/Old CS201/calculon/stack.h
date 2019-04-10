#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct {
	SQNode *topNode;
} Stack;

#endif /* Stack_h */

Stack *newStack();
void push(value *value, Stack *stack);
value *pop(Stack *stack);
value *peak(Stack *stack);
