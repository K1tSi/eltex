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
Contact* searchContact(Node* root, int);
Node* searchNode(Node* root, int);
Node* getMinNode(Node *root);
Node* getMaxNode(Node *root);
int deleteContact(Tree*, int );
void printTree(Node* root);
void printTreeAllInfo(Node* root);
void updateIndexContact(Node* root, char);
Node* genBalanceTree(Node** ArrayNode, int, int, Node* parent);
void treeToArray(Node* root, Node** array, char);
void balanseTree(Tree* tree);
void deleteTree(Node* root);
#endif /* TREE_H_ */