#include <stdio.h>
#include <string.h>
#define LEN_NAME 30
#define LEN_WORK 70
#define COUNT_OF_PHONE 100
#define LEN_PHONE 15
#define COUNT_OF_EMAIL 10
#define LEN_EMAIL 250
#define LEN_LINK 200
#define COUNT_OF_SOCIAL_NETWORK 10
#define LEN_MESSENGER 25
#define COUNT_OF_MESSENGER 15

#define MAX_SIZE 250

typedef struct Contact{
    int id;
    char firstName[LEN_NAME];
    char lastName[LEN_NAME];
    char fatherName[LEN_NAME];
    char placeOfWork[LEN_WORK];
    char jobTitle[LEN_WORK];
    char phoneNumbers[COUNT_OF_PHONE][LEN_PHONE];
    char emails[COUNT_OF_EMAIL][LEN_EMAIL];
    char linksToSocialNetwork[COUNT_OF_SOCIAL_NETWORK][LEN_LINK];
    char messengers[COUNT_OF_MESSENGER][LEN_MESSENGER];

} Contact;
int lastId(){
    static int last = 0;
    return last++;
}

void addNewContact(Contact* contacts, char* name, char* lastname, int* num_contact) 
//Добавление контакта
{
    strncpy(contacts[*num_contact].firstName, name, LEN_NAME);
    strncpy(contacts[*num_contact].lastName, lastname, LEN_NAME);
    // Устанавливаем значения имени и фамилии 
    // Зануляем все остальные строки
    memset(contacts[*num_contact].fatherName, 0, LEN_NAME);
    memset(contacts[*num_contact].placeOfWork, 0, LEN_WORK);
    memset(contacts[*num_contact].jobTitle, 0, LEN_WORK);
    memset(contacts[*num_contact].phoneNumbers[0], 0, LEN_PHONE*COUNT_OF_PHONE);
    memset(contacts[*num_contact].emails[0], 0, LEN_EMAIL*COUNT_OF_EMAIL);
    memset(contacts[*num_contact].linksToSocialNetwork[0], 0, LEN_LINK*COUNT_OF_SOCIAL_NETWORK);
    memset(contacts[*num_contact].messengers[0], 0, LEN_MESSENGER*COUNT_OF_MESSENGER);

    contacts[*num_contact].id = *num_contact;
    (*num_contact)++; // кол-во контактов ++
}
void printContactsAllInfo(Contact* contacts, int count_contacts) 
{
 printf("ID\t|\tИмя\t|\tФамилия\t|\tОтчество\t|\tМесто_работы\t|\tДолжность\t|\tТелефон\t|\tЭл.почта\t|\tСоцсеть\t|\tМессенджер |\n");
 for(int i = 0; i<count_contacts; i++)
     printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", contacts[i].id,
    contacts[i].firstName, contacts[i].lastName, contacts[i].fatherName,
    contacts[i].placeOfWork, contacts[i].jobTitle,
    contacts[i].phoneNumbers[0], contacts[i].emails[0],
    contacts[i].linksToSocialNetwork[0], contacts[i].messengers[0]);
}
void printContactsSmall(Contact* contacts, int count_contacts) 
{
 printf("ID\t|\tИмя\t|\tФамилия\t|\tТелефон\t|\tЭл.почта\t|\n");
 for(int i = 0; i<count_contacts; i++)
     printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", contacts[i].id,
    contacts[i].firstName, contacts[i].lastName,
    contacts[i].phoneNumbers[0], contacts[i].emails[0]);
}
int main()
{
    Contact contacts[MAX_SIZE];
    int count_contacts = 0;
    int* pcount = &count_contacts;
    addNewContact(contacts, "Nikita", "Sizykh", pcount);
    addNewContact(contacts, "Nikita", "Anisimov", pcount);
    printContactsSmall(contacts, count_contacts);
    printf("Текушее количество контактов: %d\n",count_contacts);
    printf("ID: %d; Имя: %s; Фамилия: %s; %ld\n", contacts[0].id, contacts[0].firstName,
    contacts[0].lastName, strlen(contacts[0].emails[0]));

}