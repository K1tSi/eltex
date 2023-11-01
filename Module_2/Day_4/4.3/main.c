#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "contact.h"
#define BUFFER_SIZE 1024

int main()
{
    Tree* treeContact = createTree();
    insert(treeContact, createContact(1,"Nikita", "Lopux"));
    insert(treeContact, createContact(2,"Aikita", "Derevko"));
    insert(treeContact, createContact(3,"Zikita", "Lebovski"));
    insert(treeContact, createContact(4,"Killer", "Bi"));
    insert(treeContact, createContact(5,"Aboba", "Kuriki"));
    //updateIndexContact(treeContact->root, 0);
    //updateIndexContact(treeContact->root, 0);
    printTree(treeContact->root);
    //printOneContactSmallInfo(searchContact(treeContact->root,1));

}
