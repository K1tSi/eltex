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

#define BUFFER_SIZE 1024
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
// Не рабочая функция
int addValueForArray(char** array, char* newValue, int numberVal, int lenPole, int countPole){ // если numberVal -1 то значение добавляется в конец 
    int countNotNull = 0;
    for(; strlen(array[countNotNull])!=0; countNotNull++)
    printf(" dfsf");
    printf("%d %d",numberVal, countNotNull);
    if(numberVal > countNotNull || countNotNull >= countPole-1) return -1;
    if(numberVal == -1){
    strncpy(array[countNotNull], newValue, lenPole);
    } else {
    strncpy(array[numberVal], newValue, lenPole);
    }
}
int updateValueForArray(Contact* contacts, char* str, char whatUpdate, int num_contact, int num_change){
    int countNotNull = 0;
    if(whatUpdate == 'f'){
        for(; strlen(contacts[num_contact].phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1 || num_change >= countNotNull) return -2;
        strncpy(contacts[num_contact].phoneNumbers[num_change], str, LEN_PHONE);
    }else if(whatUpdate == 'g'){
        for(; strlen(contacts[num_contact].emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1 || num_change >= countNotNull) return -3;
        strncpy(contacts[num_contact].emails[num_change], str, LEN_EMAIL);
    } else if(whatUpdate == 'j'){
        for(; strlen(contacts[num_contact].linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1|| num_change >= countNotNull) return -4;
        strncpy(contacts[num_contact].linksToSocialNetwork[num_change], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contacts[num_contact].messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1 || num_change >= countNotNull) return -5;
        strncpy(contacts[num_contact].messengers[num_change], str, LEN_MESSENGER);
    }
}
int updateContact(Contact* contacts, char* str, char whatUpdate, int num_contact){
    int countNotNull = 0;
    if(whatUpdate == 'a'){
        strncpy(contacts[num_contact].firstName, str, LEN_NAME);
    } else if(whatUpdate == 'b'){
        strncpy(contacts[num_contact].lastName, str, LEN_NAME);
    } else if(whatUpdate == 'c'){
        strncpy(contacts[num_contact].fatherName, str, LEN_NAME);
    } else if(whatUpdate == 'd'){
        strncpy(contacts[num_contact].placeOfWork, str, LEN_WORK);
    } else if(whatUpdate == 'e'){
        strncpy(contacts[num_contact].jobTitle, str, LEN_WORK);
    } else if(whatUpdate == 'f'){
        for(; strlen(contacts[num_contact].phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1) return -2;
        strncpy(contacts[num_contact].phoneNumbers[countNotNull], str, LEN_PHONE);
    } else if(whatUpdate == 'g'){
        for(; strlen(contacts[num_contact].emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1) return -3;
        strncpy(contacts[num_contact].emails[countNotNull], str, LEN_EMAIL);
    } else if(whatUpdate == 'j'){
        for(; strlen(contacts[num_contact].linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1) return -4;
        strncpy(contacts[num_contact].linksToSocialNetwork[countNotNull], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contacts[num_contact].messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1) return -5;
        strncpy(contacts[num_contact].messengers[countNotNull], str, LEN_MESSENGER);
    }else return -1;
    return 0;
}

int deleteContact(Contact* contacts, int id, int* count_contacts){
    if(id < *count_contacts){
        for(int i = id; i < (*count_contacts)-1; i++){
            contacts[i] = contacts[i+1];
            contacts[i].id = i;
            }
        (*count_contacts)--;
        return 0;
    }
    else return -1;
}
void printContactsAllInfo(Contact* contacts, int count_contacts) 
{
    int cPhone = 0, cEmail = 0, cLink = 0, cMessenger = 0, countNotNull = 1;
    printf("ID\t|\tИмя\t|\tФамилия\t|\tОтчество\t|\tМесто_работы\t|\tДолжность\t|\tТелефон\t|\tЭл.почта\t|\tСоцсеть\t|\tМессенджер |\n");
    for(int i = 0; i<count_contacts; i++){
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", contacts[i].id,
        contacts[i].firstName, contacts[i].lastName, contacts[i].fatherName,
        contacts[i].placeOfWork, contacts[i].jobTitle,
        contacts[i].phoneNumbers[0], contacts[i].emails[0],
        contacts[i].linksToSocialNetwork[0], contacts[i].messengers[0]);
        
        for(; strlen(contacts[i].messengers[countNotNull])!=0 || strlen(contacts[i].phoneNumbers[countNotNull])!=0 || strlen(contacts[i].linksToSocialNetwork[countNotNull]) !=0 || strlen(contacts[i].emails[countNotNull])!=0; countNotNull++) printf("\t\t\t\t\t\t\t\t\t\t\t\t%d.\t\t%s\t\t%s\t\t%s\t\t%s\n", countNotNull, 
        contacts[i].phoneNumbers[countNotNull], contacts[i].emails[countNotNull],
        contacts[i].linksToSocialNetwork[countNotNull], contacts[i].messengers[countNotNull]);
        countNotNull = 1;
        //for(; strlen(contacts[i].messengers[cEmail])!=0; cEmail++);
        //for(; strlen(contacts[i].messengers[cLink])!=0; countNotNull++);
        //for(; strlen(contacts[i].messengers[cMessenger])!=0; countNotNull++);
        
        //if(strlen())
    }
}
void printContactsSmall(Contact* contacts, int count_contacts) 
{
 printf("ID\t|\tИмя\t|\tФамилия\t|\tТелефон\t|\tЭл.почта\t|\n");
 for(int i = 0; i<count_contacts; i++)
     printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", contacts[i].id,
    contacts[i].firstName, contacts[i].lastName,
    contacts[i].phoneNumbers[0], contacts[i].emails[0]);
    //if (0);
}
int main()
{
    Contact contacts[MAX_SIZE];
    int count_contacts = 0;
    int* pcount = &count_contacts;
    char operation;
    addNewContact(contacts, "Nikita", "Sizykh", pcount);
    addNewContact(contacts, "Nikita", "Anisimov", pcount);
    updateContact(contacts,"Kirilllll", 'b', 1);
    printContactsSmall(contacts, count_contacts);
    printf("Текушее количество контактов: %d\n",count_contacts);
    deleteContact(contacts, 0, pcount);
    addNewContact(contacts, "Nikita", "Anisimov", pcount);
    //strncpy(contacts[0].firstName,"123123",30);
    
    //addValueForArray(contacts[0].phoneNumbers[0], "+79834561665", -1, LEN_PHONE, COUNT_OF_PHONE);
    updateContact(contacts, "+79834561665", 'f',1);
    updateContact(contacts, "+79834561665", 'f',1);
    updateContact(contacts, "nuk@mail.ru", 'g',1);
    updateContact(contacts, "gfreak@hotmail.ru", 'g',0);
    updateContact(contacts, "nik.nik@gmail.ru", 'g',0);
    updateContact(contacts, "nikittta@mail.ru", 'g',0);
    updateContact(contacts, "+7981232453", 'f',0);
    
    updateContact(contacts, "+79832432423", 'f',0);

    updateValueForArray(contacts, "+7xxxxxx",'f',0,1);
    printContactsAllInfo(contacts, count_contacts);
    
    while(1) {
        //system("clear");
        
        printf("Список контактов:\n");
        printContactsSmall(contacts, count_contacts);
        scanf("%c", &operation);
        //fgets(operation, 2, stdin);
        printf("%c",operation);
    }
    
}
