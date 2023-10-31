#include "list.h"
#include "contact.h"
#include <stdlib.h>


List* createList(){         // создать структуру список
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->last = NULL;
    return list;
}
Contact* getContact(List* list, int index) {        // найти контакт с определённым индексом
    Node *tmp = list->head;
 
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if(!tmp) return NULL;
    return tmp->contact;
}


int deleteContact(List* list, int index) {        // удаление контакта с определённым индексом.
    Node *tmp = list->head;
 
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if (!tmp) return -1;
    if(tmp == list->head){
        list->head = tmp->next;
        tmp->next->prev = NULL;
    } else if (tmp == list->last) {
        list->last = tmp->prev;
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }  
    free(tmp->contact);
    free(tmp);
    list->size--;
    return 0;
}

Contact* _deleteNodeSaveCont(List* list, int index) {        // удаление ноды является вспомогательной функцией
    Node *tmp = list->head;
    Contact* tmpCon;
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if (!tmp) return NULL;
    if(tmp == list->head){
        list->head = tmp->next;
        tmp->next->prev = NULL;
    } else if (tmp == list->last) {
        list->last = tmp->prev;
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }  
    tmpCon = tmp->contact;
    free(tmp);
    return tmpCon;
}

int swapContact(Node* node1, Node* node2){      // перебрасывание указателя на конакт с одной ноды на другую
    if(!node1 || !node2) return -1;
    Contact* tmp = node1->contact;
    node1->contact = node2->contact;
    node2->contact = tmp;
    return 0;
}
int inserting(List * list, Contact* con){           // вставка элементов в список, во время вставки ищется подходящее место для элемента
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->contact = con;
    tmp->next = NULL;
    tmp->prev = NULL;
    Node* next = list->head;
    Node* prev = NULL;
    if(next == NULL) list->head = tmp;
    if (list->last == NULL) {           // обработка ситуации, когда список пуст
        list->last = tmp;
        return 0;
    }
    while(equal(tmp->contact, next->contact)>=0 && next != NULL){   // пока разница между контактами больше нуля идём по циклу
        prev = next;
        next = next->next;
        if(!next) break;
    }
    if(next == NULL){
        list->last = tmp;
        tmp->prev = prev;
        prev->next = tmp;
    }else if (prev == NULL){
        list->head = tmp;
        tmp->next = next;
        next->prev = tmp;
    }else{
        tmp->next = next;
        tmp->prev = prev;
        prev->next = tmp;
        next->prev = tmp;
    }


    //while(equal(tmp->contact))
    list->size++;
}
int insert(List * list, Contact* con){          // вставка в начало (не используется)
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->contact = con;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->last == NULL) {
        list->last = tmp;
    }
    //while(equal(tmp->contact))
    list->size++;
}
int printList(List * list){         
    Node* tmp = list->head;

    while(tmp){
        printOneContactAllInfo(tmp->contact);
        tmp=tmp->next;
    }
}
int printListSmall(List * list){         
    Node* tmp = list->head;

    while(tmp){
        printOneContactSmallInfo(tmp->contact);
        tmp=tmp->next;
    }
}

void deleteList(List ** list){      // удаление всего списка
    Node* tmp = (*list)->head;
    Node* next = NULL;
    while(tmp){
        next = tmp->next;
        free(tmp->contact);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}
int changeContactName(List* list, int index, char* name) {
    Contact* tmpCon = _deleteNodeSaveCont(list, index);
    updateContact(tmpCon, name, 'a');
    inserting(list, tmpCon);

}
int updateIndexContact(List* list){
    Node* tmp = list->head;
    int index = 0;
    while(tmp){
        tmp->contact->id = index;
        index++;
        tmp=tmp->next;
    }
    return index;
}