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
Node* searchNode(Node* root, int index){        // найти Node содержащую контакт с определённым индексом
    if (root == NULL) return NULL;
    if (root->contact->id == index)
        return root;
// Поиск нужного узла
    if (index < root->contact->id)
        return searchNode(root -> left, index);
    else return searchNode(root -> right, index);
}
Node* getMinNode(Node *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}
Node* getMaxNode(Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}
int deleteContact(Tree* tree, int index){
    Node* delNode = searchNode(tree->root, index);
    if (!delNode) return -1;
    if(delNode->right == NULL && delNode->left == NULL){    // если удаляемый является листом
        Node* p = delNode->parent;
        if(p)
            if(p->left == delNode)
                p->left = NULL;
            else p->right = NULL;
        else tree->root = NULL;
        free(delNode->contact);
        free(delNode);
    } else if (delNode->right == NULL){     // если у удаляемого только одно левое поддерево
        Node* p = delNode->parent;
        if(p)
            if(p->left == delNode)
                p->left = delNode->left;
            else p->right = delNode->left;
        else tree->root = delNode->left;
        free(delNode->contact);
        free(delNode);
    }else if (delNode->left == NULL){       // если у удаляемого только одно правое поддерево
        Node* p = delNode->parent;
        if(p)
            if(p->left == delNode)
                p->left = delNode->right;
            else p->right = delNode->right;
        else tree->root = delNode->right;
        free(delNode->contact);
        free(delNode);
    } else if (delNode->left && delNode->right){    // если у удаляемого два поддерева
        Node* maxNode = getMaxNode(delNode->left); // ищем максимальный в левом поддереве
        free(delNode->contact);
        delNode->contact = maxNode->contact;
        if (maxNode->parent != delNode) {
            if(maxNode->left != NULL) maxNode->parent->right = maxNode->left; // максимальный элемент может иметь только левого потомка
            else maxNode->parent->right = NULL; // удаляем лист
            }
            // если ниже удаляемого одна вершина, удаляем лист
        else delNode->left = maxNode->left;
        free(maxNode);
    }
    updateIndexContact(tree->root, 0);
    tree->size--;
    return 0;
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