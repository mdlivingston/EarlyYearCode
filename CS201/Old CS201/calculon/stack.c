#include "stack.h"

Stack *newStack() {
	Stack *newStack = malloc(sizeof *newStack);
	newStack->topNode = NULL;
	
	return newStack;
}

void push(value *value, Stack *stack) {
	SQNode *node = newSQNode(value, stack->topNode, NULL);
	node->nextNode = stack->topNode;
	stack->topNode = node;
}

value *pop(Stack *stack) {
	SQNode *topNode = stack->topNode;
	if (topNode != NULL) {
		value *value = topNode->value;
		
		stack->topNode = topNode->nextNode;
		topNode = NULL;
		free(topNode);
		
		return value;
	}
	return 0;
}

value *peak(Stack *stack) {
	if (stack->topNode) {
		return stack->topNode->value;
	}
	return 0;
}
