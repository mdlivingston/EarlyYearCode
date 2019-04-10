
#include "queue.h"

queue *newQueue(void (*d)(FILE *,void *)){
    queue *items = malloc(sizeof(queue));
    items->list = newSLL(d);
    return items;
}

int sizeQueue(queue *items){
    return items->list->size;
}

extern void enqueue(queue *items,void *value){
    insertSLL(items->list, items->list->size, value);
}

extern void *dequeue(queue *items){
    void *poppers = removeSLL(items->list, 0);
    return poppers;
}

extern void *peekQueue(queue *items){
    return getSLL(items->list, 0);
}

extern void displayQueue(FILE *f,queue *items){
    displaySLL(f, items->list);
}
