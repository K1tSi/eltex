#include "tree.h"
#include "contact.h"
#include <stdlib.h>


Tree* createTree(){         // создать структуру список
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

int insert(Tree* tree, Contact* contact){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->parent = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->contact = contact;
    if(!tree->root){
        tree->root = tmp;
        tree->size++;
        return 0;
    }
    Node * r1 = tree->root, *prev_r1 = NULL;
    while (r1){
        prev_r1 = r1;
        if(equal(contact,r1->contact)<0)
            r1 = r1->left;
        else
            r1 = r1->right;
    }
    tmp->parent = prev_r1;
    if(equal(contact,prev_r1->contact)<0) prev_r1 ->left = tmp;
    else prev_r1->right = tmp;
    tree->size++;
    updateIndexContact(tree->root, 0);      //  при каждой вставке индексы обновляются, чтобы потом их можно было использовать для поиска по дереву
    return 0;
}
Contact* searchContact(Node* root, int index){        // найти контакт с определённым индексом // каждая запись отсортирована по имени и индексу
    if (root == NULL) return NULL;
    if (root->contact->id == index)
        return root->contact;
// Поиск нужного узла
    if (index < root->contact->id)
        return searchContact(root -> left, index);
    else return searchContact(root -> right, index);
}
void printTree(Node* root){       // делаем симметричный обход дерева
    if (root == NULL)
        return;
    printTree(root -> left);
    if (root -> contact)
        printOneContactSmallInfo(root->contact);
    printTree(root -> right);
}
void printTreeAllInfo(Node* root){       
    if (root == NULL)
        return;
    printTree(root -> left);
    if (root -> contact)
        printOneContactAllInfo(root->contact);
    printTree(root -> right);
}
void updateIndexContact(Node* root, char op){
    static int index = 0;
    if(!op) index = 0;
    if (root == NULL)
        return;
    updateIndexContact(root -> left, 1);
    if (root -> contact)
        root->contact->id = index++;
    updateIndexContact(root -> right, 1);
}