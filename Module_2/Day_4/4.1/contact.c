#include "contact.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int equal(Contact *con1, Contact * con2){
    return strcmp(con1->firstName, con2->firstName);
}
Contact* createContact(int id, char* name, char* lastname){
    Contact* contact = (Contact*)malloc(sizeof(Contact));
    strncpy(contact->firstName, name, LEN_NAME);
    strncpy(contact->lastName, lastname, LEN_NAME);
    // Устанавливаем значения имени и фамилии 
    // Зануляем все остальные строки
    memset(contact->fatherName, 0, LEN_NAME);
    memset(contact->placeOfWork, 0, LEN_WORK);
    memset(contact->jobTitle, 0, LEN_WORK);
    memset(contact->phoneNumbers[0], 0, LEN_PHONE*COUNT_OF_PHONE);
    memset(contact->emails[0], 0, LEN_EMAIL*COUNT_OF_EMAIL);
    memset(contact->linksToSocialNetwork[0], 0, LEN_LINK*COUNT_OF_SOCIAL_NETWORK);
    memset(contact->messengers[0], 0, LEN_MESSENGER*COUNT_OF_MESSENGER);

    contact->id = id;
    return contact;
}
int updateContact(Contact* contact, char* str, char whatUpdate){
    int countNotNull = 0;
    if(whatUpdate == 'a'){
        strncpy(contact->firstName, str, LEN_NAME);
    } else if(whatUpdate == 'b'){
        strncpy(contact->lastName, str, LEN_NAME);
    } else if(whatUpdate == 'c'){
        strncpy(contact->fatherName, str, LEN_NAME);
    } else if(whatUpdate == 'd'){
        strncpy(contact->placeOfWork, str, LEN_WORK);
    } else if(whatUpdate == 'e'){
        strncpy(contact->jobTitle, str, LEN_WORK);
    } else if(whatUpdate == 'f'){
        for(; strlen(contact->phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1) return -2;
        strncpy(contact->phoneNumbers[countNotNull], str, LEN_PHONE);
    } else if(whatUpdate == 'g'){
        for(; strlen(contact->emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1) return -3;
        strncpy(contact->emails[countNotNull], str, LEN_EMAIL);
    } else if(whatUpdate == 'j'){
        for(; strlen(contact->linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1) return -4;
        strncpy(contact->linksToSocialNetwork[countNotNull], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contact->messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1) return -5;
        strncpy(contact->messengers[countNotNull], str, LEN_MESSENGER);
    }else return -1;
    return 0;
}
void printOneContactAllInfo(Contact* contact){
    int countNotNull = 1;
    printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", contact->id,
        contact->firstName, contact->lastName, contact->fatherName,
        contact->placeOfWork, contact->jobTitle,
        contact->phoneNumbers[0], contact->emails[0],
        contact->linksToSocialNetwork[0], contact->messengers[0]);
        for(; strlen(contact->messengers[countNotNull])!=0 || strlen(contact->phoneNumbers[countNotNull])!=0 || strlen(contact->linksToSocialNetwork[countNotNull]) !=0 || strlen(contact->emails[countNotNull])!=0; countNotNull++) 
            printf("\t\t\t\t\t\t%d.\t%s\t%s\t%s\t%s\n", countNotNull, 
            contact->phoneNumbers[countNotNull], contact->emails[countNotNull],
            contact->linksToSocialNetwork[countNotNull], contact->messengers[countNotNull]);
}
