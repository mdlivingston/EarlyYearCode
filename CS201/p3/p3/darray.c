//
//  darray.c
//  p3
//
//  Created by Max Livingston on 3/21/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

#include "darray.h"
#include <stdlib.h>

struct DArray{
    void **array;
    int capacity;
    int size;
    void (*display)(FILE*,void*);
};
DArray *newDArray(void (*display)(FILE *,void *)){
    DArray *d = malloc(sizeof *d);
    d->capacity = 1;
    d->size = 0;
    d->array = malloc(sizeof *d->array);
    d->display = display;
    return d;
}
void changeCapacity(DArray *a) {
    if (a->size >= a->capacity) {
        a->capacity *= 2;
        a->array = realloc(a->array, sizeof *a->array * a->capacity);
    }
    if(a->size < a->capacity * .25){
        a->capacity -= a->capacity / 2;
        a->array = realloc(a->array, sizeof *a->array * a->capacity);
    }
}
void insertDArray(DArray *a,void *v){
    // make sure there's room to expand into
    changeCapacity(a);
    
    // append the value and increment vector->size
    a->array[a->size++] = v;

}
void *removeDArray(DArray *a){
    void *arr = getDArray(a, a->size-1);
    a->size--;
    changeCapacity(a);
    return arr;
}
void *getDArray(DArray *a,int index){
    if (index >= a->size) {
        return NULL;
    }
    return a->array[index];
}
void setDArray(DArray *a,int index,void *value){
    // zero fill the vector up to the desired index
    while (index >= a->size) {
        insertDArray(a, 0);
    }
    // set the value at the desired index
    a->array[index] = value;
}
int sizeDArray(DArray *a){
    return a->size;
}
void displayDArray(FILE *fp,DArray *a){
    fprintf(fp,"[");
    for (int i = 0; i< a->size; i++){
        if(i>0){
            fprintf(fp,",");
        }
        
        a->display(fp,a->array[i]);
    }
    fprintf(fp,"]");
    fprintf(fp,"[%d]",a->capacity - a->size);
}
