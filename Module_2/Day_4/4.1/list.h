#include "contact.h"
#ifndef LIST_H_
#define LIST_H_
typedef struct Node{
    struct Contact* contact;
    struct Node* next;
    struct Node* prev;
} Node;
typedef struct List{
    unsigned int size;
    struct Node* head;
    struct Node* last;
} List;
List* createList();
int insert(List *, Contact*);
List* fromArray(Contact*, int, int);
void deleteList(List **);
int printList(List *);
int swapContact(Node*, Node*);
int inserting(List *, Contact*);
int deleteContact(List* , int);
int changeContactName(List*, int, char*);
Contact* _deleteNodeSaveCont(List*, int);
#endif /* LIST_H_ */