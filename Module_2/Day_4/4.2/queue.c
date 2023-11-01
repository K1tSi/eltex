#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
Queue* createQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->first=NULL;
    queue->last=NULL;
    queue->size=0;
    return queue;
}
int insert(Queue* queue, int value, unsigned char priority){
    if(priority<1) return -1;
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->information = value;
    tmp->priority = priority;
    tmp->next = NULL;
    tmp->prev = NULL;
    if(0 == queue->size){
        queue->first = tmp;
        queue->last = tmp;
        queue->size++;
        return 0;
    }
    Node* next = queue->last;
    Node* prev = NULL;
    while(next){
        prev = next;
        if(next->priority <= tmp->priority) { break;}
        next=next->prev;
    }
    if(next == queue->last) {
        tmp->prev = next;
        next->next = tmp;
        queue->last = tmp;
    } else if(!next){
        queue->first = tmp;
        tmp->next = prev;
        prev->prev = tmp;
    } else{
        tmp->next = next->next;  // следующий за некстом с меньшим приоритетом будет следующим после tmp
        if(next->next)
            next->next->prev =tmp;
        next->next = tmp; 
        tmp->prev = next;
        
 
    }
    queue->size++;
    return 0;
}
int getInformation(Queue* queue, short priority){
    Node* tmp = queue->first;
    int info;
    if(!tmp) return -2;
    if(priority == 0 ){
        queue->first=tmp->next;
        if(tmp->next)
            tmp->next->prev = NULL;
        info = tmp->information;
        free(tmp);
        queue->size--;
        return info;
    } else if(priority > 0){
        while(tmp){
            if(tmp->priority == priority) break;
            tmp = tmp->next;
        }
        if(!tmp) return -1;
        info = tmp->information;

        if(tmp->prev)
            tmp->prev->next = tmp->next;
        else queue->first = tmp->next;  // если у данного элемента предыдущий нулевой, значит этот элемент первый, и наоборот
        if(tmp->next)
            tmp->next->prev = tmp->prev;
        else queue->last = tmp->prev;
        queue->size--;
        free(tmp);
        return info;

    } else if(priority < 0){
        while(tmp){
            if(0-(short)tmp->priority >= priority) break;  // -100  > -99 не до конца ясно что за знак тут должен быть 
            tmp = tmp->next;
        }
        if(!tmp) return -3;
        info = tmp->information;

        if(tmp->prev)
            tmp->prev->next = tmp->next;
        else queue->first = tmp->next;  // аналогично предыдущей записи
        if(tmp->next)
            tmp->next->prev = tmp->prev;
        else queue->last = tmp->prev;
        queue->size--;
        free(tmp);
        return info;

    }


}
void printQueue(Queue* queue){
    Node* tmp = queue->first;
    int index = 0;
    if(!tmp) printf("Empty queue!\n");
    while(tmp){
        printf("Number in Queue: %-3d; Priority: %-3d; Value: %d\n", index++, tmp->priority, tmp->information);
        tmp= tmp->next;
    }
    printf("\n");
}