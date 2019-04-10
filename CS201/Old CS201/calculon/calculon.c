/*
 * El Calculon
 *
 *    written by Max Livingston
 *
 *      ~Calculon is a calculator that uses stacks, queues, and a binary search tree to calculate infix expressions.
 *
 *          It can convert infix to postfix as well.~
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "scanner.h"
#include "queue.h"
#include "stack.h"
#include "binarysearchtree.h"
#include "node.h"
#include <math.h>


void Fatal(char *,...);



int priority(char);
int precedence(char);
void inftopost(FILE *f);
char *stringRipper(char *, char);
float calculator(Stack *stack, Stack *stack2);
char *stringbuilder(Stack*);

int main(int argc, char *argv[]) {
    
    char *v1;
    
    
    value num;
    value num2;
    value total;
    Queue *Q = newQueue();
    Stack *S = newStack();
    Stack *S2 = newStack();
    BinarySearchTree *B = newBinarySearchTree();
    FILE *f = stdin;
    
    //Print Name Switch
    if(argc == 2 && strcmp(argv[1], "-v") == 0)
    {
        printf("%s\n","Max Livingston");
        return 0;
    }
    
    //Infix to Postfix from a File
    if(argc == 3 && strcmp(argv[1], "-d") == 0)
    {
        f = fopen(argv[2], "r");
        inftopost(f);
        printf("\n");
        return 0;
    }
    
    //Infix to Postfix from Stdin
    else if(argc == 2 && strcmp(argv[1], "-d") == 0)
    {
        inftopost(f);
        printf("\n");
        return 0;
    }
    
    //Calculate from a file
    else if(argc == 2)
    {
        f = fopen(argv[1], "r");
    }
    
    //Store Variables and Fill Queue
    while (!feof(f))
    {
        bool allStrings = true;
        
        while ((v1 = readToken(f))  && strcmp(v1, ";"))
        {
            if (strstr(v1, "\"") == NULL && strcmp(v1, "+"))
            {
                allStrings = false;
            }
            v1 = stringRipper(v1,'"');
            if (!strcmp(v1, "var"))
            {
                value *var = newStringValue(readToken(f));
                readToken(f);
                var->rval = atof(readToken(f));
                var->type = VARIABLE;
                insertNode(var, B);
            }
            if (strcmp(v1, ";"))
            {
                if(isalpha(v1[0]) && strcmp(v1, "var"))
                {
                    BSTNode *node = searchTree(&v1[0],B);
                    if ( node != NULL)
                    {
                        enqueue(node->value, Q);
                    }
                    else
                    {
                       enqueue(newStringValue(v1), Q);
                    }
                }
                
                else if (strcmp(v1, "var"))
                {
                    enqueue(newStringValue(v1), Q);
                }
            }
        }
        
        //Start Calculations using Stacks
        while (!isEmpty(Q))
        {
            value *str;
            str = dequeue(Q);
            
            if (allStrings == true)
            {
                push(str,S);
                dequeue(Q);
                push(dequeue(Q),S);
                printf("\"%s\"\n",stringbuilder(S));
            }
            
            else if (!strcmp(str->sval, "+") || !strcmp(str->sval, "-") || !strcmp(str->sval, "/") || !strcmp(str->sval, "*")|| !strcmp(str->sval, ";" ) || !strcmp(str->sval, "^" ) || !strcmp(str->sval, "%" ))
            {
                while(peak(S2) && precedence(*peak(S2)->sval) >= precedence(*str->sval))
                {
                    float temp = calculator(S, S2);
                    value *temp2 = newRealValue(temp);
                    push(temp2, S);
                }
                if(!peak(S2))
                {
                    push(str, S2);
                }
                else
                {
                    push(str, S2);
                }
            }
            
            else if (!strcmp(str->sval, "("))
            {
                push(str,S2);
            }
            
            else if (!strcmp(str->sval, ")"))
            {
                float cal = calculator(S,S2);
                value *cal1 = newRealValue(cal);
                push(cal1,S);
                pop(S2);
            }
            else if (str->type == VARIABLE)
            {
                push(str, S);
            }
            else if (str->type == STRING)
            {
                str->rval = atof(str->sval);
                push(str, S);
            }
            else
            {
                total.rval = calculator(S,S2);
                push(&total,S);
            }
        }
        
        while (peak(S2))
        {
            num.rval = calculator(S, S2);
            push(&num, S);
        }
        
        if (peak(S))
        {
            num2 = *pop(S);
            if (floor(num2.rval) - num2.rval != 0.0f)
            {
                printf("%.2lf\n", num2.rval);
            }
            else
            {
                printf("%.0lf\n", num2.rval);
            }
        }
        
    }
    return 0;
}

char *stringRipper(char *string, char c)
{
    char *newString = malloc(strlen(string));
    int count = 0;
    
    for (int i = 0; i < strlen(string); ++i)
    {
        if (string[i] != c )
        {
            newString[count] = string[i];
            ++count;
        }
    }
    
    newString = realloc(newString, count);
    newString[count] = '\0';
    
    return newString;
}

char *stringbuilder(Stack *stack)
{
    
    char *str1;
    char *str2;
    
    str1 = pop(stack)->sval;
    str2 = pop(stack)->sval;
    strcat(newStringValue(str2)->sval,newStringValue(str1)->sval);
    
    return str2;
}
float calculator(Stack *stack, Stack *stack2)
{
    char *op;
    float num;
    float num2;
    value total;
    
    num = pop(stack)->rval;
    op = pop(stack2)->sval;
    num2 = pop(stack)->rval;
    
    if (!strcmp(op, "+"))
    {
        total.rval = num2 + num;
        return total.rval;
    }
    if (!strcmp(op, "-"))
    {
        total.rval = num2 - num;
        return total.rval;
    }
    if (!strcmp(op, "*"))
    {
        total.rval = num2 * num;
        return total.rval;
    }
    if (!strcmp(op, "/"))
    {
        total.rval = num2 / num;
        return total.rval;
    }
    if (!strcmp(op, "^"))
    {
        total.rval = pow(num2, num);
        return total.rval;
    }
    if (!strcmp(op, "%"))
    {
        total.rval = fmod(num2, num);
        return total.rval;
    }
    return 0;
}

//For Infix to Postfix
int priority(char x)
{
    if(x == '(' || x == ')')
        return(0);
    if(x == '+' || x == '-')
        return(1);
    if(x == '*' || x == '/')
        return(2);
    return(3);
    
}

//For Order of Operations
int precedence(char x)
{
    if(x == '(' || x == ')')
        return(0);
    if(x == '+')
        return(1);
    if(x == '-')
        return(2);
    if(x == '*')
        return(3);
    if(x == '/')
        return(4);
    if(x == '%')
        return(5);
    if(x == '^')
        return(6);
    return(7);
}

//Infix to Postfix
void inftopost(FILE *f)
{
    char *v1 = "";
    value *x;
    value *y;
    Queue *Q = newQueue();
    Queue *Q2 = newQueue();
    Stack *S = newStack();
    BinarySearchTree *B = newBinarySearchTree();
    while (!feof(f))
    {
        
        while ((v1 = readToken(f))  && strcmp(v1, ";") )
        {
            if (!strcmp(v1, "var"))
            {
                value *var = newStringValue(readToken(f));
                readToken(f);
                var->rval = atof(readToken(f));
                var->type = VARIABLE;
                insertNode(var, B);
            }
            
            if (strcmp(v1, ";"))
            {
                if(isalpha(v1[0]) && strcmp(v1, "var"))
                {
                    BSTNode *node = searchTree(&v1[0],B);
                    if ( node != NULL)
                    {
                        enqueue(node->value, Q2);
                    }
                }
                else if (strcmp(v1, "var"))
                {
                    enqueue(newStringValue(v1), Q);
                    value *str;
                    value *str2;
                    int num;
                    
                    str = dequeue(Q);
                    num = str->ival;
                    
                    while(!isEmpty(Q2))
                    {
                        str2 = dequeue(Q2);
                        printf("%.0lf ", str2->rval);
                    }
                    
                    if (priority(*str->sval) == 3)
                    {
                        printf("%s ",str->sval);
                        
                    }
                    else
                    {
                        if (!strcmp(v1, "("))
                        {
                            push(str, S);
                        }
                        else
                        {
                            if (!strcmp(v1, ")"))
                            {
                                
                                while(peak(S) && strcmp(peak(S)->sval,"("))
                                {
                                    
                                    printf("%s ",pop(S)->sval);
                                }
                                pop(S);
                                
                            }
                            else
                            {
                                while (peak(S) && priority(str->sval[0]) <= priority(*peak(S)->sval))
                                {
                                    x = pop(S);
                                    printf("%s ",x->sval);
                                }
                                push(newStringValue(v1), S);
                                
                            }
                        }
                        
                    }
                }
            }
        }
        
        while (!isEmpty(Q2))
        {
            y = dequeue(Q2);
            printf("%.0lf\n", y->rval);
        }
        
        while (peak(S) != NULL)
        {
            x=pop(S);
            printf("%s\n",x->sval);
        }
        
    }
    
    
}

void Fatal(char *fmt, ...)
{
    va_list ap;
    
    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    
    exit(-1);
}
