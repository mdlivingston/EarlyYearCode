#include "CDLL.h"

struct node * newNode(struct vertex *value){
    struct node *newNode = malloc(sizeof(*newNode));
    newNode->data = value->data;
    newNode->degree = 0;
    newNode->children = NULL;
    newNode->vertex = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    
    return newNode;
}


struct node * makeCDLL(){
    struct node *makeCDLL = malloc(sizeof(*makeCDLL));
    makeCDLL->next= NULL;
    makeCDLL->prev=NULL;
    makeCDLL->data = INT_MAX;
    makeCDLL->children = 0;
    makeCDLL->size = 0;
    makeCDLL = NULL;
    
    return makeCDLL;
}


// Function to merge two linked lists
struct node *merge(struct node *first, struct node *second)
{
    // If first linked list is empty
    if (!first)
        return second;
    
    // If second linked list is empty
    if (!second)
        return first;
    
    // Pick the smaller value
    if (first->data < second->data)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Function to do merge sort
struct node *mergeSort(struct node *head)
{
    if (!head || !head->next)
        return head;
    struct node *second = split(head);
    
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
    
    // Merge the two sorted halves
    return merge(head,second);
}

// A utility function to insert a new node at the
// beginning of doubly linked list
void insert(struct node **head, struct node *data)
{
    struct node *temp =
    (struct node *)malloc(sizeof(*head));
    temp = data;
    temp->next = temp->prev = NULL;
    if (!(*head)){
        (*head) = temp;
                
    }
    else
    {
        temp->next = *head;
        (*head)->prev = temp;
        (*head) = temp;
        temp->prev = *head;
    }
    (*head)->size++;
    
}

struct node *deleteNode(struct node **head, struct node **del)
{
    /* base case */
    if(*head == NULL || del == NULL)
        return NULL;
    
    /* If node to be deleted is head node */
    if((*head) == (*del)){
        *head = (*del)->next;
        (*del)->next = NULL;
    }
    
    /* Change next only if node to be deleted is NOT the last node */
    if((*del)->next != NULL)
        (*del)->next->prev = (*del)->prev;
    
    /* Change prev only if node to be deleted is NOT the first node */
    if((*del)->prev != NULL)
        (*del)->prev->next = (*del)->next;
    if((*del)->prev == NULL && (*del)->next == NULL ){
    }
    return *head;
}


// Utility function to swap two integers
void swap(int *A, int *B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}

// Split a doubly linked list (DLL) into 2 DLLs of
// half sizes
struct node *split(struct node *head)
{
    struct node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct node *temp = slow->next;
    slow->next = NULL;
    return temp;
}


