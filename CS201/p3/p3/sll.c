
#include "sll.h"

sll *newSLL(void (*d)(FILE *,void *)){ //d is the display funciton
    sll *items = malloc(sizeof(sll));
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

sllnode *newSLLNODE(void *allo){
    sllnode *newSLLNODE = malloc(sizeof(*newSLLNODE));
    newSLLNODE->next = NULL;
    newSLLNODE->value = allo;
    return newSLLNODE;
}

int sizeSLL(sll *SLL){
    return SLL->size;
}


void displaySLL(FILE *f, sll *SLL){
    sllnode *temp = SLL->head;
    if(SLL->head == NULL){
        fprintf(f, "[]");
    }
    else{
        fprintf(f, "[");
        int flag = 0;
        while(temp){
            if(flag > 0){
                fprintf(f, ",");
            }
            SLL->display(f, temp->value);
            temp = temp->next;
            flag++;
        }
        fprintf(f, "]");
    }
}

void *getSLL(sll *items, int index){
    sllnode *temp = items->head;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }
//    if(temp == NULL){
//        return 0;
//    }
    return temp->value;
}

void insertSLL(sll *SLL, int index, void *value){
    sllnode *node = newSLLNODE(value);
    sllnode *temp = SLL->head;
    sllnode *tempTail = newSLLNODE(value);
    
    
    if(SLL->head == NULL && SLL->tail == NULL){
        SLL->head = node;
        SLL->tail = node;
    }
    else if(index == 0){
        if(SLL->head){
            node->next = SLL->head;
        }
        SLL->head = node;
    }
    else if(index == SLL->size){
            tempTail = SLL->tail;
            SLL->tail = node;
        tempTail->next = node;
    }
    else{
        for (int i = 0; i<index - 1; i++){
            if(temp->next){
                temp = temp->next;
            }
        }
        sllnode *temp2 = temp->next;
        
        temp->next = node;
        
        if(temp2 != NULL){
            temp->next->next = temp2;
        }
        else{
            SLL->tail = temp->next;
            SLL->tail->next = NULL;
        }
    }
    SLL->size++;
}

void *removeSLL(sll *items,int index){
    sllnode *temp = items->head;
    sllnode *temp2 = newSLLNODE(NULL);
   
    if(index > items->size - 1){
        return temp;
    }
    
    for(int i = 0; i < index - 1 ; i++){
        if(temp == NULL){
            return temp2;
        }
        if(temp->next == NULL){
            return temp2;
        }
        temp = temp->next;
    }
    temp2 = temp->next;
    if(temp == items->head && temp == items->tail){
        items->head = NULL;
        items->tail = NULL;
        temp2 = temp;
    }
    else if (index == 0){
        temp2 = temp;
        temp = temp->next;
        items->head = temp;
    }
    else if(temp->next == items->tail){
        temp->next = NULL;
        items->tail = temp;
    }
    else{
        temp->next = temp->next->next;
    }
    items->size--;
    return temp2->value;
}


void unionSLL(sll *rep, sll *donor){
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
        sllnode *temp = rep->tail;
        temp->next = donor->head;
        rep->tail = donor->tail;
        rep->tail->next = NULL;
        rep->size = rep->size + donor->size;
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
    }
    
}
