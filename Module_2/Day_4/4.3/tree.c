#include "tree.h"
#include "contact.h"
#include <stdlib.h>


Tree* createTree(){         // создать структуру список
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if(!tree) return NULL;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

int insert(Tree* tree, Contact* contact){
    Node* tmp = (Node*)malloc(sizeof(Node));
    if(!tmp) return -1;
    tmp->parent = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->contact = contact;
    if(!tree->root){
        tree->root = tmp;
        tree->size++;
        updateIndexContact(tree->root, 0); 
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
            else 
                p->right = delNode->left;
        else 
            tree->root = delNode->left;
        delNode->left->parent = p;
        free(delNode->contact);
        free(delNode);
    }else if (delNode->left == NULL){       // если у удаляемого только одно правое поддерево
        Node* p = delNode->parent;
        if(p)
            if(p->left == delNode)
                p->left = delNode->right;
            else
                p->right = delNode->right;
        else tree->root = delNode->right;
        delNode->right->parent = p;
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
    tree->size--;
    updateIndexContact(tree->root, 0);
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
    printTreeAllInfo(root -> left);
    if (root -> contact)
        printOneContactAllInfo(root->contact);
    printTreeAllInfo(root -> right);
}
void updateIndexContact(Node* root, char reset){
    static int index = 0;
    if(!reset) index = 0;
    if (root == NULL)
        return;
    updateIndexContact(root -> left, 1);
    if (root -> contact)
        root->contact->id = index++;
    updateIndexContact(root -> right, 1);
}
Node* genBalanceTree(Node** ArrayNode, int i, int j, Node* parent){     // принимает массив указателей на ноды и возвращает корень нового сбалансированного дерева
    if(i > j) return NULL;
    else{
        Node* tmp = (Node*)malloc(sizeof(Node));
        int k = i + (j-i)/2;
        tmp->contact = ArrayNode[k]->contact;
        tmp->parent = parent;
        tmp->left = genBalanceTree(ArrayNode, i, k-1, tmp);
        tmp->right = genBalanceTree(ArrayNode, k+1, j, tmp);
        return tmp;
    }
}
void treeToArray(Node* root, Node** array, char op){        // преобразование дерева из нод в массив указателей
    static int i = 0;
    if(!op) i = 0;
    if (root == NULL)
        return;
    treeToArray(root -> left, array, 1);
    array[i] = root;
    i++;
    treeToArray(root -> right, array, 1);

}
void balanseTree(Tree* tree){
    if((tree->size) < 4) return;
    Node** array = (Node**)malloc(sizeof(Node*)*tree->size);
    treeToArray(tree->root, array, 0);
    tree->root = genBalanceTree(array, 0, tree->size-1, NULL);
    for(int i = 0; i< tree->size; i++)
        free(array[i]);
    free(array);

}
void deleteTree(Node* root){
    if (root == NULL)
        return;
    deleteTree(root -> left);
    deleteTree(root -> right);
    free(root->contact);
    free(root);
}