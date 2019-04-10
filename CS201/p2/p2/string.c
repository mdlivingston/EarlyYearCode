#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "string.h"


string *
newString(char* x)
{
    string *p = malloc(sizeof(string));
    if (p == 0){
        fprintf(stderr,"out of memory\n");
        exit(-1);
    }
    p->value = x;
    return p;
}

char*
getString(string *v)
{
    if(!v){
        return 0;
    }
    return v->value;
}

char*
setString(string *v,char* x)
{
    char* old = v->value;
    v->value = x;
    return old;
}

void
displayString(FILE *fp,void *v)
{
    fprintf(fp,"\"%s\"",getString(v));
}

int compareString(void *v,void *w){
    string *temp = v;
    string *temp2 = w;
    return strcmp(temp->value , temp2->value);

}
void
freeString(string *v)
{
    free(v);
}
