#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integer.h"


integer *
newInteger(int x)
    {
    integer *p = malloc(sizeof(integer));
        if (p == 0){
            fprintf(stderr,"out of memory\n");
            exit(-1);
        }
    p->value = x;
    return p;
    }

int 
getInteger(integer *v)
    {
        if(!v){
            return '\0';
        }
    return v->value;
    }

int 
setInteger(integer *v,int x)
    {
    int old = v->value;
    v->value = x;
    return old;
    }

void 
displayInteger(FILE *fp,void *v)
    {
    fprintf(fp,"%d",getInteger(v));
    }

int compareInteger(void *v,void *w)
{
    if(v == NULL){
        v = newInteger(INT_MIN);
    }
    if(w == NULL){
        w = newInteger(INT_MIN);
    }
    return ((integer *) v)->value - ((integer *) w)->value;
}

void
freeInteger(integer *v)
    {
    free(v);
    }
