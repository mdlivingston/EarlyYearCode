
#ifndef rbtree_h
#define rbtree_h

#include <stdio.h>
/*** red-black binary search tree class ***/

#include "bst.h"

#ifndef __RBT_INCLUDED__
#define __RBT_INCLUDED__
typedef struct rbt
{
    bst *tree;
    void (*display)(FILE *,void *);
    int (*compare)(void *,void *);
    int size;
    int words;
} rbt;

extern rbt *newRBT(void (*)(FILE *,void *),int (*)(void *,void *));
extern void insertRBT(rbt *,void *);
extern int findRBT(rbt *,void *);
extern void deleteRBT(rbt *,void *);
extern void statisticsRBT(rbt *,FILE *);
extern void displayRBT(FILE *,rbt *);
extern void checkRBT(rbt *);               //optional
#endif
#endif /* rbtree_h */
