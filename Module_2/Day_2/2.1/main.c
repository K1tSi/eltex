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
void printOneContactAllInfo(Contact* contacts, int id){
    int countNotNull = 1;
    
    printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", contacts[id].id,
        contacts[id].firstName, contacts[id].lastName, contacts[id].fatherName,
        contacts[id].placeOfWork, contacts[id].jobTitle,
        contacts[id].phoneNumbers[0], contacts[id].emails[0],
        contacts[id].linksToSocialNetwork[0], contacts[id].messengers[0]);
        for(; strlen(contacts[id].messengers[countNotNull])!=0 || strlen(contacts[id].phoneNumbers[countNotNull])!=0 || strlen(contacts[id].linksToSocialNetwork[countNotNull]) !=0 || strlen(contacts[id].emails[countNotNull])!=0; countNotNull++) 
            printf("\t\t\t\t\t\t\t\t\t\t\t%d.\t\t%s\t\t%s\t\t%s\t\t%s\n", countNotNull, 
            contacts[id].phoneNumbers[countNotNull], contacts[id].emails[countNotNull],
            contacts[id].linksToSocialNetwork[countNotNull], contacts[id].messengers[countNotNull]);
    
}

void printContactsAllInfo(Contact* contacts, int count_contacts) 
{
    int countNotNull = 1;
    printf("ID\t|\tИмя\t|\tФамилия\t|\tОтчество\t|\tМесто_работы\t|\tДолжность\t|\tТелефон\t|\tЭл.почта\t|\tСоцсеть\t|\tМессенджер |\n");
    for(int i = 0; i<count_contacts; i++){
        printOneContactAllInfo(contacts, i);
    }
}
void printContactsSmall(Contact* contacts, int count_contacts) 
{
 printf("ID\t|\tИмя\t|\tФамилия\t\t|\tТелефон\t\t|\tЭл.почта\t|\n");
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
    char operation;
    int whatdo;
    char BUFFER[BUFFER_SIZE];
    char BUFFER1[BUFFER_SIZE];
    int BUFFINT, BUFFINT2;

// Инициализация начальных данных в контактах
    addNewContact(contacts, "Nikita", "Sizykh", pcount);
    addNewContact(contacts, "Nikita", "Anisimov", pcount);
    updateContact(contacts,"Gigachad", 'b', 0);
    deleteContact(contacts, 1, pcount);
    addNewContact(contacts, "Nikita", "Anisimov", pcount);
    updateContact(contacts, "Студент", 'e', 0);
    updateContact(contacts, "Вуз", 'd', 0);
    updateContact(contacts, "vk.com/id01010101", 'j', 0);
    updateContact(contacts, "@niiiiiita", 'k', 0);
    updateContact(contacts, "Студент", 'e', 1);
    updateContact(contacts, "ВУЗ", 'd', 1);
    updateContact(contacts, "vk.com/anisik", 'j', 1);
    updateContact(contacts, "@anime", 'k', 1);
    updateContact(contacts, "+79834561665", 'f',1);
    updateContact(contacts, "+79834561665", 'f',1);
    updateContact(contacts, "nuk@mail.ru", 'g',1);
    updateContact(contacts, "gfreak@hotmail.ru", 'g',0);
    updateContact(contacts, "nik.nik@gmail.ru", 'g',0);
    updateContact(contacts, "nikittta@mail.ru", 'g',0);
    updateContact(contacts, "+7981232453", 'f',0);
    updateContact(contacts, "+79832432423", 'f',0);
    updateValueForArray(contacts, "+7xxxxxx",'f',0,1);

    addNewContact(contacts, "Kirill", "Temnikov", pcount);
    updateContact(contacts, "88005553535", 'f',2);
    updateContact(contacts, "reclama@adddd.ru", 'g',2);

// пользовательское меню в беск. цикле

    while(1) {

        system("clear");
        fflush(stdin);
        printf("Список контактов:\n");
        printContactsSmall(contacts, count_contacts);
        printf("Текушее количество контактов: %d\n",count_contacts);    
        printf("Выбери действие:\n");
        printf("1 - Создать новый контакт\n"
        "2 - Удалить контакт\n"
        "3 - Обновить контакт\n"
        "4 - Вывести полную информацию о контактах\n"
        "5 - Выйти\n");
        scanf("%d", &whatdo);




        switch(whatdo){
            case 1:
                printf("Введите имя и фамилию:\n");
                scanf("%s %s", BUFFER,BUFFER1);
                addNewContact(contacts, BUFFER, BUFFER1, pcount);
                break;
            case 2:
                printf("ВведитеID удаляемого контакта:\n");
                scanf("%d", &BUFFINT);
                deleteContact(contacts, BUFFINT, pcount);
                break;
            case 3:
                printf("Введите ID обновляемого контакта:\n");
                scanf("%d", &BUFFINT);
                if(BUFFINT > count_contacts-1) break;
                printf("ID\t|\tИмя(a)\t|\tФамилия(b)\t|\tОтчество(c)\t|\tМесто_работы(d)\t|\tДолжность(e)\t|\tТелефон(f)\t|\tЭл.почта(g)\t|\tСоцсеть(j)\t|\tМессенджер(k) |\n");
                printOneContactAllInfo(contacts, BUFFINT);
                printf("Введите, что вы хотите обновить (введите один символ который указан после нужного поля)\n");
                scanf("%c", &operation);
                while(operation=='\n') scanf("%c", &operation);
                if(operation == 'f' || operation == 'g' || operation == 'j' || operation == 'k'){
                    printf("Вы хотите перезаписать или добавить ещё одно значение? (1 - перезаписать; 0 - добавить)\n");
                    scanf("%d", &BUFFINT2);
                    if(BUFFINT2){
                        printf("Введите номер изменяемого поля (Самое первое поле имеет номер 0)\n");
                        scanf("%d", &BUFFINT2);
                        printf("Введите новое значение поля:\n");
                        scanf("%s", BUFFER);
                        updateValueForArray(contacts, BUFFER, operation, BUFFINT, BUFFINT2);
                        break;
                    }
                }
                printf("Введите новое значение поля:\n");
                scanf("%s", BUFFER);
                updateContact(contacts, BUFFER, operation, BUFFINT);
                
                break;
            case 4:
                printContactsAllInfo(contacts,count_contacts);
                getc(stdin);
                printf("\n.....Нажмите Enter.....\n");
                getc(stdin);
                break;
            case 5:
                return 0;
                break;    
            default:
                
        }

    }
    
}
