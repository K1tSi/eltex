#ifndef QUEUE_H_
#define QUEUE_H_
typedef struct Node{
    int information;
    unsigned char priority;
    struct Node* next;
    struct Node* prev;
} Node;
typedef struct Queue{
    int size;
    struct Node* first;
    struct Node* last;
} Queue;
Queue* createQueue();
int insert(Queue*, int, unsigned char);
int getInformation(Queue*, short);
void printQueue(Queue*);
#endif /* QUEUE_H_ */