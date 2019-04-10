/*
 *  Prim's Pandora
 *
 *    written by Max Livingston
 *
 *      ~Where there is a heap there is a tree~
 *
 *          ~This assignment pushed me where I needed to go, for that I thank you, Dr. Lusth.~
 */



#include <stdio.h>
#include <math.h>
#include <string.h>
#include "stdlib.h"
#include "CDLL.h"
#include "binheap.h"
#include "scanner.h"
#include "graph.h"
#include "queue.h"



Binheap* makeVertexArray(struct Graph *graph);
struct Graph *createMatrix(FILE *f);
struct vertex *Prims(struct Graph *graph, Binheap *b, int parent[], int key[]);
void bfs(struct vertex *printLL, int parent[], int weight[], struct Graph *graph);
Binheap *buildBin(struct Graph *b);
void proveBinheap(Binheap *b);
void proveMatrix(struct Graph *Graph);
int main(int argc, char * argv[]){
    
    FILE *f = fopen(argv[1], "r");
    
    struct Graph *graph = createMatrix(f);
    Binheap *binHeap = buildBin(graph);
    int parent[graph->V];   // Array to store constructed MST
    int key[graph->V];      // Key values used to pick minimum weight edge in cut
    
    for (int v = 0; v < graph->V; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        
    }
    
    if(argv[2]){
        f = fopen(argv[1], "r");
        struct Graph *graph = createMatrix(f);
        Binheap *binHeapTest = buildBin(graph);
        proveBinheap(binHeapTest);
        proveMatrix(graph);
        printf("\nPrinting out MST in BFS Order....\n\n");
    }
    
    Prims(graph, binHeap, parent, key);
    return 0;
}

void proveBinheap(Binheap *b){
    printf("Extracting Min from the Binomial Heap that is filled with text file data....\n\n");
    while(b->size > 0){
        printf("%d ", extractMin(b)->data);
    }
    printf("\n\n");
}


void proveMatrix(struct Graph *graph){
    int V = graph->V;
    printf("Printing out Adjacency Matrix....\n\n");
    for(int i = 0; i < V; i++){
        struct node* pCrawl = graph->array[i].head;
        printf("%d->", i);
        while(pCrawl != NULL){
            printf("% d", pCrawl->data);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

struct vertex *Prims(struct Graph *graph, Binheap *b, int parent[], int key[]){
    int loopFlag = 0;
    struct vertex *whirlV = NULL;
    while (b->size > 0)
    {
        
        struct node *minNode = extractMin(b);
        int u = minNode->data;
        struct node* pCrawl = graph->array[u].head;
        
        if(loopFlag != 0  && minNode->vertex->key == INT_MAX){
            insertBin(b, minNode->vertex);
            break;
        }
        
        if(loopFlag == 0){
            whirlV = minNode->vertex;
            loopFlag++;
        }
        
        while (pCrawl != NULL)
        {
            int v = pCrawl->data;
            struct vertex* p = graph->array[v].startV;
            if(b->size != 0){
                if ( (p->heapFlag == 0  && pCrawl->vertex->key < key[v]) || (p->heapFlag == 0 && parent[v] ==  u))
                {
                    key[v] = pCrawl->vertex->key;
                    parent[v] = u;
                    p->predecessor = minNode;
                    decreaseKey(b, p->owner, key[v]);
                }
            }
            pCrawl = pCrawl->next;
        }
    }
    
    bfs(whirlV, parent, key, graph);
    while(b->size > 0){
        whirlV = Prims(graph, b, parent, key);
    }
    return whirlV;
}

void bfs(struct vertex *printLL, int parent[], int key[], struct Graph *graph){
    Queue *bftQ = newQueue();
    value *startvert = newIntegerValue(printLL->data);
    enqueue(startvert, bftQ);
    enqueue(NULL, bftQ);
    struct node* LL = makeCDLL();
    int sCount = 0;
    int weight = 0;
    
    while(bftQ->backNode != NULL){
        value *v = dequeue(bftQ);
        if(v != NULL){
            struct vertex* tempVert = newVertexNode(v->ival, 0);
            struct node* tempNode = newNode(tempVert);
            if(sCount == 0){
                printf("%d : %d", sCount, v->ival);
            }
            else if(bftQ->backNode->value == NULL){
                insert(&LL, tempNode);
            }
            else{
                insert(&LL, tempNode);
            }
            struct node *pCrawl = graph->array[v->ival].head;
            while(pCrawl != NULL){
                if(parent[pCrawl->data] == v->ival){
                    value *nextP = newIntegerValue(pCrawl->data);
                    enqueue(nextP, bftQ);
                }
                pCrawl = pCrawl->next;
            }
        }
        else{
            if(bftQ->backNode != NULL || LL){
                LL = mergeSort(LL);
                while(LL){
                    
                    if(LL->prev == NULL){
                        
                        printf("%d : %d(%d)%d", sCount,  LL->data, parent[LL->data], key[LL->data]);
                        weight = weight + key[LL->data];
                    }
                    else{
                        if(LL->prev->data != LL->data){
                            printf(", %d(%d)%d", LL->data, parent[LL->data], key[LL->data]);
                            weight = weight + key[LL->data];
                        }
                    }
                    
                    LL = LL->next;
                }
                printf(";\n");
                sCount++;
                enqueue(NULL, bftQ);
                LL = makeCDLL();
            }
            else
            {
                if(LL){
                    printf("%d(%d)%d", LL->data, parent[LL->data], key[LL->data]);
                    weight = weight + key[LL->data];
                }
                if(weight == 0){
                    printf(";\nweight: %d\n", weight);
                }
                else{
                    printf("weight: %d\n", weight);
                }
                break;
            }
        }
    }
}

Binheap* buildBin(struct Graph *graph){
    int V = graph->V;
    Binheap *b = newBinHeap(*comparator);
    for (int i =0; i<V; i++ ){
        struct node* pCrawl = graph->array[i].head;
        struct vertex* p = graph->array[i].startV;
        if(pCrawl != NULL){
            insertBin(b, p);
        }
        
    }
    return b;
}

struct Graph *createMatrix(FILE *f){
    char *v1;
    
    Queue *Q = newQueue();
    int large = 0;
    
    while (!feof(f))
    {
        int i = 0;
        while ((v1 = readToken(f)))
        {
            if(!strcmp(v1, ";") && i == 2){
                value *one = newIntegerValue(1);
                enqueue(one, Q);
            }
            if(strcmp(v1, ";")){
                value *vert;
                if (i != 2) {
                    if(atoi(v1) > large){
                        large = atoi(v1);
                    }
                    vert = newIntegerValue(atoi(v1));
                } else {
                    vert = newIntegerValue(atof(v1));
                }
                
                enqueue(vert, Q);
            }
            i++;
            if(!strcmp(v1, ";")){
                i = 0;
            }
        }
    }
    
    struct Graph *graph = createGraph(large+1);
    int arr[large];
    int vert1 = '\0';
    int vert2 = '\0';
    int weight = '\0';
    for (int v = 0; v < large; ++v)
    {
        arr[v] = 0;
    }
    
    while(Q->backNode != NULL){
        vert1 = dequeue(Q)->ival;
        vert2 = dequeue(Q)->ival;
        weight = dequeue(Q)->ival;
        addEdge(graph, vert1, vert2, weight);
    }
    return graph;
}

