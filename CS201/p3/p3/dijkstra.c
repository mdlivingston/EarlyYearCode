//
//  main.c
//  p3
//
//  Created by Max Livingston on 3/21/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "darray.h"
#include "binomial.h"
#include "queue.h"
#include "scanner.h"
#include "vertex.h"

DArray *createMatrix(FILE *f);
Binomial* buildBin(DArray *graph);
void dijkstra(Binomial*b,DArray*a);
void displayDijkstra(FILE *fp,DArray *b);

int main(int argc, const char * argv[]) {
    FILE *f = fopen(argv[1], "r");
    DArray *graph = createMatrix(f);
    Binomial *binHeap = buildBin(graph);
    dijkstra(binHeap, graph);
    return 0;
}
void dijkstra(Binomial*b,DArray*a){
    if(sizeBinomial(b) == 0 && sizeDArray(a) == 0){
        fprintf(stdout,"%d:\n",0);
        fprintf(stdout,"----\n");
    }
    DArray *bfsArray = newDArray(displayVertexValue);
    while(sizeBinomial(b) > 0){
        vertex *u = extractBinomial(b);
        if(u->key == INT_MAX){
            u->key = 0;
            insertBinomial(b, u);
            break;
        }
        vertex *v = getDArray(a, u->value);
        for(int i = 0; i < sizeDArray(v->neighbors); i++){
            vertex *newV = getDArray(v->neighbors, i);
            vertex *vChecker = getDArray(a, i);
            if(getDArray(v->neighbors, i) && vChecker->visited == 0 && u->key + newV->key < vChecker->key){
                vChecker->pred = u->value;
                vChecker->key = newV->key + u->key;
                decreaseKeyBinomial(b, vChecker->node, vChecker);
            }
        }
        u->visited = 1;
        insertDArray(bfsArray, u);
    }
    displayDijkstra(stdout, bfsArray);
    if(sizeBinomial(b)){
        dijkstra(b,a);
    }
}
extern void displayDijkstra(FILE *fp,DArray *b){
    if(sizeDArray(b) == 0){
        return;
    }
    int counter = 0;
    int lineNum = 0;
    queue *Q = newQueue(displayVertexValue);
    Binomial *bin = newBinomial(displayVertexValue, compareVertex, updateVertex);
    vertex *roots = getDArray(b, counter);
    if(b){
        fprintf(fp,"%d :",lineNum);
        Q = newQueue(NULL);
        enqueue(Q, roots);
        insertBinomial(bin, roots);
        enqueue(Q, NULL);
        counter++;
    }
    else{
        fprintf(fp,"%d:\n",lineNum);
        fprintf(fp,"\n----\n");
        return;
    }
    while(sizeQueue(Q) > 0){
        vertex *node = dequeue(Q);
        if(sizeQueue(Q) == 0){
            fprintf(fp,"\n----\n");
            break;
        }
        if(!node){
            while(sizeBinomial(bin) > 0){
                vertex *noder = extractBinomial(bin);
                fprintf(fp," ");
                fprintf(fp,"%d",noder->value);
                if(noder->pred != -1){
                    fprintf(fp,"(");
                    fprintf(fp,"%d",noder->pred);
                    fprintf(fp,")");
                    fprintf(fp,"%d",noder->key);
                }
                if(noder == roots){
                    fprintf(fp,"\n");
                    lineNum++;
                    fprintf(fp,"%d :",lineNum);
                }
            }
            if(counter != sizeDArray(b)){
                fprintf(fp,"\n");
                lineNum++;
                fprintf(fp,"%d :",lineNum);
                enqueue(Q, NULL);
            }
        }
        else{
            for(int i = 0; i < sizeDArray(b); i++){
                vertex *printers = getDArray(b, i);
                if(printers->pred == node->value){
                    counter++;
                    insertBinomial(bin, printers);
                    enqueue(Q, printers);
                }
            }
        }
    }
}

Binomial* buildBin(DArray *graph){
    Binomial *binHeap = newBinomial(displayVertexValue, compareVertex, updateVertex);
    int flag = 0;
    for (int i = 0; i < sizeDArray(graph); i++){
        if(getDArray(graph, i)){
            vertex *v = getDArray(graph, i);
            v->key = INT_MAX;
            if(flag == 0){
                v->key = 0;
            }
            v->pred = -1;
            BinomialNode *node = insertBinomial(binHeap, v);
            vertex *otherNode = getDArray(graph, i);
            otherNode->node = node;
            flag++;
        }
    }
    return binHeap;
}
int getEdge(vertex*v1, vertex*v2){
    vertex *edge = getDArray(v1->neighbors, v2->value);
    if(edge){
        return edge->key;
    }
    return 0;
}
DArray *createMatrix(FILE *f){
    char *v1;
    char *v2;
    DArray *vertArray = newDArray(displayVertexValue);
    while (!feof(f))
    {
        v1 =readToken(f);
        while(v1){
            int vr1 = atoi(v1);
            vertex * newVertex = newVertexNode(newInteger(vr1),displayVertexValue);
            if(vr1 < sizeDArray(vertArray)){
                if(getDArray(vertArray, vr1)){
                    newVertex = getDArray(vertArray, vr1);
                }
            }
            v2 = readToken(f);
            int vr2 = atoi(v2);
            vertex * newVertex2 = newVertexNode(newInteger(vr2),displayVertexValue);
            if(vr2 < sizeDArray(vertArray)){
                if(getDArray(vertArray, vr2)){
                    newVertex2 = getDArray(vertArray, vr2);
                }
            }
            vertex *newVertex3 = newVertexNode(newInteger(vr1),displayVertexValue);
            vertex *newVertex4 = newVertexNode(newInteger(vr2),displayVertexValue);
            if(vr2 < sizeDArray(newVertex->neighbors)){
                if(getDArray(newVertex->neighbors, vr2)){
                    newVertex4 = getDArray(newVertex->neighbors, vr2);
                }
            }
            if(vr1 < sizeDArray(newVertex2->neighbors)){
                if(getDArray(newVertex2->neighbors, vr1)){
                    newVertex3 = getDArray(newVertex2->neighbors, vr1);
                }
            }
            setDArray(newVertex->neighbors, newVertex4->value, newVertex4);
            setDArray(newVertex2->neighbors, newVertex3->value, newVertex3);
            if(newVertex->value == newVertex2->value){
                v1 =readToken(f);
                if(strcmp(v1, ";")){
                    v1 = readToken(f);
                }
            }
            else{
                v1 = readToken(f);
                if(!strcmp(v1, ";")){
                    vertex *neighbor1 = getDArray(newVertex->neighbors, newVertex2->value);
                    neighbor1->key = 1;
                    vertex *neighbor2 = getDArray(newVertex2->neighbors, newVertex->value);
                    neighbor2->key = 1;
                }
                else{
                    int oldEdge = getEdge(newVertex, newVertex2);
                    int newEdge = atoi(v1);
                    if(oldEdge == 0 || newEdge < oldEdge){
                        vertex *neighbor1 = getDArray(newVertex->neighbors, newVertex2->value);
                        neighbor1->key = newEdge;
                        vertex *neighbor2 = getDArray(newVertex2->neighbors, newVertex->value);
                        neighbor2->key = newEdge;
                    }
                    v1 = readToken(f);
                }
                setDArray(vertArray, newVertex->value, newVertex);
                setDArray(vertArray, newVertex2->value, newVertex2);
            }
            v1 = readToken(f);
        }
    }
    return vertArray;
}

