#include <stdio.h>
#include <string.h>
#include "list.h"
#include "contact.h"


int main()
{
    List* listContact = createList();
    Contact* cont = createContact(1,"Nakita","Sizyh");
    inserting(listContact, cont);
    printOneContactAllInfo(cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "Вуз", 'd');
    updateContact(cont, "vk.com/id01010101", 'j');
    updateContact(cont, "gfreak@hotmail.ru", 'g');
    updateContact(cont, "nik.nik@gmail.ru", 'g');
    updateContact(cont, "nikittta@mail.ru", 'g');
    updateContact(cont, "+7981232453", 'f');
    updateContact(cont, "+79832432423", 'f');


    cont = createContact(2,"Niruto","Golinkov");
    inserting(listContact, cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "ВУЗ", 'd');
    updateContact(cont, "vk.com/anisik", 'j');
    updateContact(cont, "@anime", 'k');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "nuk@mail.ru", 'g');
    //swapContact(listContact->head, listContact->head->next);
    printList(listContact);

    cont = createContact(3,"Kirill", "Temnikov");
    inserting(listContact, cont);
    updateContact(cont, "88005553535", 'f');
    updateContact(cont, "reclama@adddd.ru", 'g');
    printList(listContact);


    inserting(listContact, createContact(4,"Bbbbbbbbb", "Temnikov"));
    inserting(listContact, createContact(5,"Aaaaaaaaaa", "Temnikov"));
    inserting(listContact, createContact(6,"ZaaR", "Temnikov"));
    printList(listContact);
    deleteContact(listContact, 3);
    
    changeContactName(listContact, 1, "Artem");
    printList(listContact);
}
