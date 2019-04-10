/*
 * Let There Be Trees!
 *
 *    written by Max Livingston
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "libs.h"
#include <math.h>



char *stringRipper(char*, int*);
char *getString(FILE*,char*);
bool stringBuilder(char*);

void showStatistics(BinarySearchTree*,int);
void shortestPath(BinarySearchTree*);
void longestPath(BinarySearchTree*);

int main(int argc, char *argv[]){
    char *v1;
    char *v2;
    int avlFlag = 0;
    int nodes = 0;
    
    BinarySearchTree *B = newBinarySearchTree();
    
    FILE *f = fopen(argv[2], "r");
    FILE *f2 = fopen(argv[3],"r");
    
    // Read Value Before End of File
    
    v1 = readToken(f);
    
    // Read Corpus
    
    if(!strcmp(argv[1],"-b")){
        while(!feof(f)){
            int toggle = 0;
            if (stringBuilder(v1) == true){
                char *t = v1;
                t = realloc(t, strlen(t) + 1);
                strcat(t, " ");
                v1 = getString(f, t);
                v1 = v1 + 1;
                toggle = 1;
            }
            if(v1 != NULL){
                v1 = stringRipper(v1, &toggle);
                int duplicate = 0;
                insertNode(v1, B, &duplicate);
                if(!duplicate){
                    nodes++;
                }
                v1 = readToken(f);
                
            }
            
        }
    }
    
    else if (!strcmp(argv[1], "-a")){
        while(!feof(f)){
            int toggle = 0;
            avlFlag = 1;
            int duplicate = 0;
            if (stringBuilder(v1) == true){
                char *t = malloc(strlen(t));
                t = realloc(t, strlen(t) + 1);
                strcat(t, " ");
                v1 = getString(f, t);
                v1 = v1 + 1;
                toggle = 1;
            }
            if(v1 != NULL){
                v1 = stringRipper(v1, &toggle);
                if (strcmp(v1, "")){
                    insertNodeAVL(v1, B, &duplicate);
                    if(!duplicate){
                        nodes++;
                    }
                    
                }
                v1 = readToken(f);
            }
        }
    }
    else{
        printf("Please Enter '-b' for BST Tree or '-a' for AVL Tree.\n");
        return 0;
    }
    
    // Read Commands
    
    while(!feof(f2))
    {
        while ((v2 = readToken(f2)))
        {
            
            // Insert Word or Phrase
            
            int duplicate = 0;
            if (!strcmp(v2, "i")){
                v2 = readToken(f2);
                int toggle = 0;
                if (stringBuilder(v2) == true){
                    char *t = v2;
                    t = realloc(t, strlen(t) + 1);
                    strcat(t, " ");
                    v2 = getString(f2, t);
                    v2 = v2 + 1;
                    toggle = 1;
                }
                
                if(!strcmp(argv[1], "-b")){
                    int duplicate = 0;
                    v2 = stringRipper(v2, &toggle);
                    insertNode(v2, B, &duplicate);
                    if(!duplicate){
                        nodes++;
                    }
                }
                
                if(!strcmp(argv[1], "-a")){
                    v2 = stringRipper(v2, &toggle);
                    insertNodeAVL(v2, B, &duplicate);
                }
                if(!duplicate){
                    nodes++;
                }
            }
            
            // Display Report of Tree
            
            if (!strcmp(v2, "r")){
                printf("The number of nodes in the tree is: %d\n", nodes);
                shortestPath(B);
                longestPath(B);
            }
            
            // Display Frequency of Node
            
            if (!strcmp(v2, "f")){
                v2 = readToken(f2);
                int toggle = 0;
                if (stringBuilder(v2) == true){
                    char *t = v2;
                    t = realloc(t, strlen(t) + 1);
                    strcat(t, " ");
                    v2 = getString(f2, t);
                    v2 = v2 + 1;
                    toggle = 1;
                }
                v2 = stringRipper(v2, &toggle);
                
                if (searchTree(v2, B) == NULL)
                {
                    printf("%s'%s'%s\n", "Word or Phrase: ",v2, " does not exists");
                }
                else{
                    BSTNode frequency = *searchTree(v2, B);
                    printf("%s'%s'%s%d\n","The Frequency of ", v2, " is: ",frequency.freq);
                }
            }
            
            // Delete Node from Tree
            
            if(!strcmp(v2, "d")){
                v2 = readToken(f2);
                if (searchTree(v2, B) == NULL){
                    printf("%s'%s'%s\n", "Word or Phrase: ",v2, " does not exists");
                }
                else{
                    if(!strcmp(argv[1], "-a")){
                        deleteAVL(B, v2);
                        printf("%s'%s'%s\n", "Word or Phrase: ",v2, " has been deleted");
                        
                    }
                    else{
                        deleteNode(v2, B);
                        nodes--;
                        printf("%s'%s'%s\n", "Word or Phrase: ",v2, " has been deleted");
                        
                    }
                }
            }
            
            // Display Statistics of Tree
            
            if (!strcmp(v2, "s")){
                showStatistics(B, avlFlag);
            }
        }
    }
}

// Finds Longest Path to a Leaf

void longestPath(BinarySearchTree *B){
    Queue *Q = buildQueue(B,0);
    BSTNode *token = dequeue(Q);
    int i = 0;
    while(!isEmpty(Q) || token != 0){
        if(token == NULL){
            i++;
            while (token == NULL){
                token = dequeue(Q);
            }
        }
        token = dequeue(Q);
    }
    printf("The distance of the longest path to a NULL pointer is: %d\n", i);
}

// Finds the Shortest Path to a Leaf

void shortestPath(BinarySearchTree *B){
    Queue *Q = buildQueue(B,0);
    BSTNode *token = dequeue(Q);
    int i = 0;
    while(!isEmpty(Q) || token != 0){
        
        if(token == NULL){
            i++;
            while (token == NULL){
                token = dequeue(Q);
            }
        }
        else{
            if(B->root->left == NULL || B->root->right == NULL){
                i= 0;
                printf("The distance of the shortest path to a NULL pointer: %d\n",i);
                break;
                
            }
            if (token->left==NULL || token->right == NULL) {
                printf("The distance of the shortest path to a NULL pointer: %d\n",i);
                i--;
                break;
            }
            else{
                token = dequeue(Q);
            }
        }
    }
}



char *getString(FILE *file, char *string) {
    char *token = readToken(file);
    
    while (1) {
        string = realloc(string, strlen(token) + strlen(token) + strlen(string));
        strcat(string, token);
        if (!strstr(token, "\"")) {
            strcat(string, " ");
        } else {
            string[strlen(string) - 1] = '\0';
            string = realloc(string, strlen(token));
            
            break;
        }
        
        token = readToken(file);
    }
    
    return string;
}

void showStatistics(BinarySearchTree *B, int flag){
    Queue *Q ;
    if(flag){
        Q = buildQueue(B,1);
    }
    else{
        Q = buildQueue(B,0);
    }
    int i = 0;
    
    printf("%d: ",i++);
    BSTNode *token = dequeue(Q);
    
    while(!isEmpty(Q) || token != 0){
        char sign = '\0';
        if(token != NULL && flag == 1){
            if(token->left != NULL && token->right != NULL){
                if(token->left->height > token->right->height){
                    sign = '-';
                }
                if(token->left->height < token->right->height){
                    sign = '+';
                }
            }
            if(token->left == NULL && token->right != NULL){
                sign = '+';
            }
            if(token->left != NULL && token->right == NULL){
                sign = '-';
            }
        }
        
        if(token == NULL){
            printf("\n%d: ", i++);
        }
        else{
            if (token->parent == NULL){
                if(token->left==NULL && token->right == NULL){
                    if (flag == 1 && sign != '\0'){
                        token->sign = sign;
                        printf("=%s%c(%s%c)%dX", token->value, sign, token->value, sign, token->freq);
                        
                    }
                    else{
                        printf("=%s(%s)%dX", token->value, token->value,token->freq);
                    }
                }
                else{
                    if (flag == 1 && sign != '\0'){
                        token->sign = sign;
                        printf("%s%c(%s%c)%dX", token->value, sign, token->value, sign ,token->freq);
                    }
                    else{
                        printf("%s(%s)%dX", token->value, token->value,token->freq);
                    }
                    
                }
            }
            else{
                if (token->parent->left == token){
                    if(token->left==NULL && token->right == NULL){
                        if (flag == 1 && sign != '\0'){
                            token->sign = sign;
                            if(token->parent->sign == '\0'){
                                printf("=%s%c(%s)%dL", token->value, sign, token->parent->value, token->freq);
                            }
                            else{
                                printf("=%s%c(%s%c)%dL", token->value, sign, token->parent->value, token->parent->sign , token->freq);
                            }
                        }
                        else{
                            if(token->parent->sign == '\0'){
                                printf("=%s(%s)%dL", token->value, token->parent->value, token->freq);
                                
                            }
                            else if (flag == 1){
                                printf("=%s(%s%c)%dL", token->value, token->parent->value, token->parent->sign , token->freq);
                            }
                            else{
                                printf("=%s(%s)%dL", token->value, token->parent->value,token->freq);
                            }
                        }
                        
                        if (Q->backNode != NULL && Q->backNode->value != NULL){
                            printf(" ");
                        }
                    }
                    
                    else{
                        if (flag == 1 && sign != '\0'){
                            token->sign = sign;
                            if(token->parent->sign == '\0'){
                                printf("%s%c(%s)%dL", token->value, sign, token->parent->value, token->freq);
                            }
                            else{
                                printf("%s%c(%s%c)%dL", token->value, sign, token->parent->value, token->parent->sign , token->freq);
                            }
                        }
                        else{
                            if(token->parent->sign == '\0'){
                                printf("%s(%s)%dL", token->value, token->parent->value, token->freq);
                            }
                            else if (flag == 1){
                                printf("%s(%s%c)%dL", token->value, token->parent->value, token->parent->sign , token->freq);
                            }
                            else{
                                printf("%s(%s)%dL", token->value, token->parent->value,token->freq);
                            }
                        }
                        if (Q->backNode != NULL && Q->backNode->value != NULL){
                            printf(" ");
                        }
                        
                    }
                }
                else{
                    if(token->left==NULL && token->right == NULL){
                        if (flag == 1 && sign != '\0'){
                            token->sign = sign;
                            if(token->parent->sign == '\0'){
                                printf("=%s%c(%s)%dR", token->value, sign, token->parent->value, token->freq);
                            }
                            else{
                                printf("=%s%c(%s%c)%dR", token->value, sign, token->parent->value, token->parent->sign , token->freq);
                            }
                        }
                        else{
                            if(token->parent->sign == '\0'){
                                printf("=%s(%s)%dR", token->value, token->parent->value, token->freq);
                            }else if (flag == 1){
                                printf("=%s(%s%c)%dR", token->value, token->parent->value, token->parent->sign , token->freq);
                            }
                            else{
                                printf("=%s(%s)%dR", token->value, token->parent->value,token->freq);
                            }
                            
                        }
                        if (Q->backNode != NULL && Q->backNode->value != NULL){
                            printf(" ");
                        }
                        
                    }
                    
                    else{
                        if (flag == 1 && sign != '\0'){
                            token->sign = sign;
                            if(token->parent->sign == '\0'){
                                printf("%s%c(%s)%dR", token->value, sign, token->parent->value, token->freq);
                            }
                            else{
                                printf("%s%c(%s%c)%dR", token->value, sign, token->parent->value, token->parent->sign , token->freq);
                            }
                        }
                        else{
                            if(token->parent->sign == '\0'){
                                printf("%s(%s)%dR", token->value, token->parent->value, token->freq);
                            }
                            else if (flag == 1){
                                printf("%s(%s%c)%dR", token->value, token->parent->value, token->parent->sign , token->freq);
                            }
                            else{
                                printf("%s(%s)%dR", token->value, token->parent->value,token->freq);
                            }
                            
                        }
                        if (Q->backNode != NULL && Q->backNode->value != NULL){
                            
                            printf(" ");
                        }
                        
                    }
                    
                }
            }
        }
        token = dequeue(Q);
    }
    printf("\n");
}

bool stringBuilder(char *string){
    bool flag = false;
    
    for (int i = 0; i < strlen(string); ++i){
        if (string[i] == '"') {
            flag = true;
        }
    }
    return flag;
    
}
char *stringRipper(char *string, int *keepSpace){
    char *newString = malloc(strlen(string));
    int count = 0;
    
    for (int i = 0; i < strlen(string); ++i){
        if (keepSpace && isspace(string[i])) {
            newString[count] = string[i];
            
            ++count;
        }
        else if (isalpha(string[i])){
            newString[count] = string[i];
            ++count;
        }
    }
    
    newString = realloc(newString, count);
    newString[count] = '\0';
    
    
    return newString;
}

