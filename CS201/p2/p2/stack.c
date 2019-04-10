#include "stack.h"

stack *newStack(void (*d)(FILE *,void *)){
    stack *items = malloc(sizeof(stack));
    if(items == 0){
        printf("Error...");
        exit(-1);
    }
    items->stack = newDLL(d);
    return items;
}

int sizeStack(stack *items){
    return items->stack->size;
}

extern void push(stack *items, void *value){
    insertDLL(items->stack, 0, value);
}

extern void *pop(stack *items){
    void *poppers = removeDLL(items->stack, 0);
    return poppers;
}

extern void *peekStack(stack *items){
    return getDLL(items->stack, 0);
}

extern void displayStack(FILE *f,stack *items){
    displayDLL(f, items->stack);
}
