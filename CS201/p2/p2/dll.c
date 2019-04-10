
#include "dll.h"

dll *newDLL(void (*d)(FILE *,void *)) //d is the display funciton
{
    dll *items = malloc(sizeof(dll));
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

dllnode *newDLLNODE(void *allo)
{
    dllnode *newDLLNODE = malloc(sizeof(*newDLLNODE));
    newDLLNODE->next = NULL;
    newDLLNODE->prev = NULL;
    newDLLNODE->value = allo;
    
    return newDLLNODE;
}

int sizeDLL(dll *DLL){
    return DLL->size;
}

dllnode *findNode(dll *items, int index){
    int halfer = items->size / 2;
    dllnode *temp = items->head;
    dllnode *tempTail = items->tail;
    if (halfer <= index){
        for(int i = items->size; i > index; i--){
            tempTail = tempTail->prev;
        }
        return tempTail;
    }
    else if (halfer >= index){
        for(int i = 0; i < index -1; i++){
            temp = temp->next;
        }
        return temp;
    }
    else{
        return 0;
    }
}
void displayDLL(FILE *f, dll *DLL){
    dllnode *temp = DLL->head;
    if(DLL->head == NULL){
        fprintf(f, "[]");
    }
    else{
        fprintf(f, "[");
        int flag = 0;
        while(temp){
            if(flag > 0){
                fprintf(f, ",");
            }
            DLL->display(f, temp->value);
            temp = temp->next;
            flag++;
        }
        fprintf(f, "]");
    }
}

void *getDLL(dll *items, int index){
    dllnode *temp = items->head;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }
    if(temp == NULL){
        return 0;
    }
    return temp->value;
}

void insertDLL(dll *DLL, int index, void *value)
{
    dllnode *node = newDLLNODE(value);
    if(!DLL->head){
        DLL->head = node;
        DLL->tail = node;
    }
    else{
        
        if(index == DLL->size){         // Inserting in the back
            DLL->tail->next = node;
            if(DLL->size == 1){
                DLL->head->next = node;
            }
            node->prev = DLL->tail;
            DLL->tail = node;
           
            DLL->size++;
            return;
        }
        if(index == 0){                 //Inserting in  the front
            node->next = DLL->head;
            DLL->head->prev = node;
            if(DLL->head == DLL->tail){
                DLL->tail->next = NULL;
            }
            DLL->head = node;
            DLL->size++;
            return;
        }
        dllnode *foundNode = findNode(DLL, index);
        
        node->prev = foundNode;
        node->next = foundNode->next;
        foundNode->next = node;
        if(node->next != NULL){
            node->next->prev = node;
        }
       
        if(index >= DLL->size){
            DLL->tail = node;
        }
    }
    
    DLL->size++;
}

void *removeDLL(dll *items,int index){
    dllnode *temp = items->head;
    dllnode *temp2 = newDLLNODE(NULL);
    if(index > items->size){
        return 0;
    }
    if(index + 1 == items->size && items->head != items->tail){
        temp2 = items->tail;
        items->tail = items->tail->prev;
        items->tail->next = NULL;
        items->size--;
        return temp2->value;
    }
    if(!items->head){
        return 0;
    }
    temp2 = temp->next;
    if(temp == items->head && temp == items->tail){
        items->head = NULL;
        items->tail = NULL;
        temp2 = temp;
    }
    else if (index == 0){
        temp2 = temp;
        items->head = temp2->next;
        items->head->prev = NULL;
    }
    else{
        temp = findNode(items, index);
        temp2 = temp->next;
        if(temp->next->next){
        temp->next = temp->next->next;
        }
        if(temp->next){
        temp->next->prev = temp;
        }
    }
    items->size--;
    return temp2->value;
}


void unionDLL(dll *rep, dll *donor){
    if(rep->head == NULL || rep->tail == NULL){
        rep->head = donor->head;
        rep->tail = donor->tail;
        rep->size = rep->size + donor->size;
        donor->head = 0;
        donor->tail = 0;
        donor->size = 0;
    }
    else if(donor->head == NULL || donor->tail == NULL){
    }
    else if(rep == donor){
        
    }
    else{
        dllnode *temp = rep->tail;
        donor->head->prev = rep->tail;
        temp->next = donor->head;
        rep->tail = donor->tail;
        rep->tail->next = NULL;
        rep->size = rep->size + donor->size;
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
    }
    
}
