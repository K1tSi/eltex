#include "contact.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int equal(Contact *con1, Contact * con2){
    return strcmp(con1->firstName, con2->firstName);
}
Contact* createContact(int id, char* name, char* lastname){
    Contact* contact = (Contact*)malloc(sizeof(Contact));
    if(!contact) return contact;
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
    if(!contact) return -11;
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
int updateValueForArray(Contact* contact, char* str, char whatUpdate, int num_change){
    int countNotNull = 0;
    if(!contact) return -11;
    if(whatUpdate == 'f'){
        for(; strlen(contact->phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1 || num_change >= countNotNull) return -2;
        strncpy(contact->phoneNumbers[num_change], str, LEN_PHONE);
    }else if(whatUpdate == 'g'){
        for(; strlen(contact->emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1 || num_change >= countNotNull) return -3;
        strncpy(contact->emails[num_change], str, LEN_EMAIL);
    } else if(whatUpdate == 'j'){
        for(; strlen(contact->linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1|| num_change >= countNotNull) return -4;
        strncpy(contact->linksToSocialNetwork[num_change], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contact->messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1 || num_change >= countNotNull) return -5;
        strncpy(contact->messengers[num_change], str, LEN_MESSENGER);
    }
    return 0;
}
void printOneContactAllInfo(Contact* contact){
    if(!contact) return;
    int countNotNull = 1;
    printf("%d\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", contact->id,
        contact->firstName, contact->lastName, contact->fatherName,
        contact->placeOfWork, contact->jobTitle,
        contact->phoneNumbers[0], contact->emails[0],
        contact->linksToSocialNetwork[0], contact->messengers[0]);
        for(; strlen(contact->messengers[countNotNull])!=0 || strlen(contact->phoneNumbers[countNotNull])!=0 || strlen(contact->linksToSocialNetwork[countNotNull]) !=0 || strlen(contact->emails[countNotNull])!=0; countNotNull++) 
            printf("\t\t\t\t\t\t\t\t\t%d. %-15s\t%-10s\t%-10s\t%-10s\n", countNotNull, 
            contact->phoneNumbers[countNotNull], contact->emails[countNotNull],
            contact->linksToSocialNetwork[countNotNull], contact->messengers[countNotNull]);
}
void printOneContactSmallInfo(Contact* contact){
    if(!contact) return;
    printf("%d\t%-10s\t%-10s\t%-10s\t%-10s\n", contact->id,
        contact->firstName, contact->lastName,
        contact->phoneNumbers[0], contact->emails[0]);
}
void copyContact(Contact *con1, Contact * con2){
    if(!con1 || !con2) return;
    int countNotNull = 0;
    con1->id = con2->id;
    strncpy(con1->firstName, con2->firstName, LEN_NAME);
    strncpy(con1->lastName, con2->lastName, LEN_NAME);
    strncpy(con1->fatherName, con2->fatherName, LEN_NAME);
    strncpy(con1->placeOfWork, con2->placeOfWork, LEN_WORK);
    strncpy(con1->jobTitle, con2->jobTitle, LEN_WORK);
    
    for(; strlen(con2->linksToSocialNetwork[countNotNull]) !=0; countNotNull++)
        strncpy(con1->linksToSocialNetwork[countNotNull], con2->linksToSocialNetwork[countNotNull], LEN_MESSENGER);   
    countNotNull = 0;
    for(; strlen(con2->emails[countNotNull])!=0; countNotNull++)
        strncpy(con1->emails[countNotNull], con2->emails[countNotNull], LEN_EMAIL);
    countNotNull = 0;
    for(; strlen(con2->messengers[countNotNull])!=0; countNotNull++)
        strncpy(con1->messengers[countNotNull], con2->messengers[countNotNull], LEN_MESSENGER);
    countNotNull = 0;
    for(; strlen(con2->phoneNumbers[countNotNull])!=0; countNotNull++)
        strncpy(con1->phoneNumbers[countNotNull], con2->phoneNumbers[countNotNull], LEN_MESSENGER);

}