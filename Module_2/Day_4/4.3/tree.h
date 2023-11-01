#include "contact.h"
#ifndef TREE_H_
#define TREE_H_
typedef struct Node{
    struct Contact* contact;
    struct Node* right;
    struct Node* left;
    struct Node* parent;
} Node;
typedef struct Tree{
    unsigned int size;
    struct Node* root;
} Tree;
Tree* createTree();
int insert(Tree*, Contact*);
Contact* searchContact(Node*, int);
void printTree(Node*);
void printTreeAllInfo(Node*);
void updateIndexContact(Node* root, char);
#endif /* TREE_H_ */