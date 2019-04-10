#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include "scanner.h"
#include "queue.h"
#include "string.h"

char *stringRipper(char *str);
void runCommands(FILE *f2,vbst *vBST, rbt *rBT, const char * argv[], FILE *f3);
void runData(FILE *f, vbst *vtree, rbt *rtree, const char *argv[]);
int main(int argc, const char * argv[]) {
    FILE *f = fopen(argv[2], "r");
    FILE *f2 = fopen(argv[3],"r");
    FILE *f3 = fopen(argv[4],"w");
    vbst *vtree = newVBST(displayString, compareString);
    rbt *rtree = newRBT(displayString, compareString);
    runData(f, vtree, rtree, argv);
    runCommands(f2, vtree, rtree, argv,f3);
    return 0;
}
void runData(FILE *f, vbst *vtree, rbt *rtree, const char *argv[]){
    char *v1;
    if((strcmp(argv[1], "-v") == 0)){
        while(!feof(f)){
            if(stringPending(f)){
                v1 = readString(f);
            }
            else{
                v1 = readToken(f);
            }
            if(v1 ==  NULL){
                break;
            }
            v1 = stringRipper(v1);
            if(strcmp(v1, "")){
                insertVBST(vtree, newString(v1));
            }
        }
    }
    else if((strcmp(argv[1], "-r") == 0)){
        while(!feof(f)){
            if(stringPending(f)){
                v1 = readString(f);
            }
            else{
                v1 = readToken(f);
            }
            if(v1 ==  NULL){
                break;
            }
            v1 = stringRipper(v1);
            if(strcmp(v1, "")){
                insertRBT(rtree, newString(v1));
            }
        }
    }
    else{
        fprintf(stderr,"unknown flag '%s',", &argv[1][1]);
        fprintf(stderr," valid flags are -d, -r, -s, and -v\n");
    }
}
void runCommands(FILE *f2, vbst *vtree, rbt *rtree, const char *argv[], FILE *f3){
    char *v2;
    v2 = readToken(f2);
    while(!feof(f2))
    {
        if (!strcmp(v2, "i")){
            if(!strcmp(argv[1], "-v")){
                if(stringPending(f2)){
                    v2 = readString(f2);
                }
                else{
                    v2 = readToken(f2);
                }
                v2 = stringRipper(v2);
                if(strcmp(v2, "")){
                    insertVBST(vtree, newString(v2));
                }
            }
            if(!strcmp(argv[1], "-r")){
                if(stringPending(f2)){
                    v2 = readString(f2);
                }
                else{
                    v2 = readToken(f2);
                }
                v2 = stringRipper(v2);
                if(strcmp(v2, "")){
                    insertRBT(rtree, newString(v2));
                }
            }
        }
        else if (!strcmp(v2, "r")){
            if(!strcmp(argv[1], "-v")){
                if(argv[4] == NULL){
                    statisticsVBST(vtree,stdout);
                }
                else{
                    statisticsVBST(vtree, f3);
                }
            }
            if(!strcmp(argv[1], "-r")){
                if(argv[4] == NULL){
                    statisticsRBT(rtree,stdout);
                }
                else{
                    statisticsRBT(rtree, f3);
                }
            }
        }
        else if (!strcmp(v2, "f")){
            if(stringPending(f2)){
                v2 = readString(f2);
            }
            else{
                v2 = readToken(f2);
            }
            v2 = stringRipper(v2);
            if(!strcmp(argv[1], "-v")){
                if(argv[4] == NULL){
                    fprintf(stdout,"Frequency of ");
                    vtree->display(stdout,newString(v2));
                    fprintf(stdout,": %d\n",findVBST(vtree, newString(v2)));
                }
                else{
                    fprintf(f3,"Frequency of ");
                    vtree->display(f3,newString(v2));
                    fprintf(f3,": %d\n",findVBST(vtree, newString(v2)));
                }
            }
            if(!strcmp(argv[1], "-r")){
                if(argv[4] == NULL){
                    fprintf(stdout,"Frequency of ");
                    rtree->display(stdout,newString(v2));
                    fprintf(stdout,": %d\n",findRBT(rtree, newString(v2)));
                }
                else{
                    fprintf(f3,"Frequency of ");
                    rtree->display(f3,newString(v2));
                    fprintf(f3,": %d\n",findRBT(rtree, newString(v2)));
                }
            }
        }
        else if(!strcmp(v2, "d")){
            if(stringPending(f2)){
                v2 = readString(f2);
            }
            else{
                v2 = readToken(f2);
            }
            v2 = stringRipper(v2);
            if(!strcmp(argv[1], "-v")){
                deleteVBST(vtree, newString(v2));
            }
            if(!strcmp(argv[1], "-r")){
            }
        }
        else if (!strcmp(v2, "s")){
            if(!strcmp(argv[1], "-v")){
                if(argv[4] == NULL){
                    displayVBST(stdout, vtree);
                }
                else{
                    displayVBST(f3, vtree);
                }
            }
            if(!strcmp(argv[1], "-r")){
                if(argv[4] == NULL){
                    displayRBT(stdout, rtree);
                }
                else{
                    displayRBT(f3, rtree);
                }
            }
        }
        v2 = readToken(f2);
    }
}
char *stringRipper(char *str){
    int j = 0;
    for(int i = 0; str[i]; i++){
        if(isalpha(str[i])){
            str[j] = tolower(str[i]);
            j++;
        }
        if(isspace(str[i])){
            str[j] = ' ';
            while(isspace(str[i]) || ((!isalpha(str[i])) && str[i])){
                i++;
            }
            i--;
            j++;
        }
    }
    str[j] = '\0';
    return str;
}

