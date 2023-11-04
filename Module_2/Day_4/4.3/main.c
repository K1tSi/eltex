#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "contact.h"
#define BUFFER_SIZE 1024
#define NUM_CONT_BEFORE_UPD 10
void changeContactName(Tree* treeContact, int BUFFINT, char* BUFFER, Contact* changeCon){
    if(treeContact->size < 1) return;
    Contact* tmp = createContact(0," ", " ");
    copyContact(tmp,changeCon);
    deleteContact(treeContact, BUFFINT);
    strncpy(tmp->firstName, BUFFER, LEN_NAME);
    insert(treeContact, tmp);
}
int main()
{
    char BUFFER[BUFFER_SIZE], BUFFER1[BUFFER_SIZE], operation;
    int BUFFINT, BUFFINT2, whatdo, index = 0, countOperation=0;
    Tree* treeContact = createTree();

    Contact* cont = createContact(index++,"Nikita","Sizykh");
    insert(treeContact, cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "Вуз", 'd');
    updateContact(cont, "vk.com/id01010101", 'j');
    updateContact(cont, "gfreak@hotmail.ru", 'g');
    updateContact(cont, "nik.nik@gmail.ru", 'g');
    updateContact(cont, "nikittta@mail.ru", 'g');
    updateContact(cont, "+7981232453", 'f');
    updateContact(cont, "+79832432423", 'f');

    cont = createContact(index++,"Naruto","Udzumake");
    insert(treeContact, cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "ВУЗ", 'd');
    updateContact(cont, "vk.com/anisik", 'j');
    updateContact(cont, "@anime", 'k');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "nuk@mail.ru", 'g');

    cont = createContact(index++,"Kirill", "Temnikov");
    insert(treeContact, cont);
    updateContact(cont, "88005553535", 'f');
    updateContact(cont, "reclama@adddd.ru", 'g');

    insert(treeContact, createContact(index++,"Nikita", "Lopux"));
    insert(treeContact, createContact(index++,"Aikita", "Derevko"));
    insert(treeContact, createContact(index++,"Zikita", "Lebovski"));
    insert(treeContact, createContact(index++,"Killer", "Bi"));
    insert(treeContact, createContact(index++,"Aboba", "Kuriki"));
    insert(treeContact, createContact(index++,"Kolya", "BMW"));
    insert(treeContact, createContact(index++,"Lisa", "Bobova"));
    balanseTree(treeContact);
    printTree(treeContact->root);

     while(1) {
        if(countOperation%NUM_CONT_BEFORE_UPD == 9) balanseTree(treeContact);
        system("clear");
        fflush(stdin);
        printf("Список контактов:\n");
        printf("%s\t%-15s\t%-10s\t%-10s\t%-10s\n","ID","|Имя","|Фамилия","|Телефон","|Эл.почта\n");
        printTree(treeContact->root);
        printf("Текушее количество контактов: %d\n",treeContact->size);    
        printf("Выбери действие:\n");
        printf("1 - Создать новый контакт\n"
        "2 - Удалить контакт\n"
        "3 - Обновить контакт\n"
        "4 - Вывести полную информацию о контактах\n"
        "6 - Выйти\n");
        scanf("%d", &whatdo);
        switch(whatdo){
            case 1:
                printf("Введите имя и фамилию:\n");
                scanf("%s %s", BUFFER,BUFFER1);
                insert(treeContact, createContact(index++,BUFFER, BUFFER1));
                countOperation++;
                break;
            case 2:
                printf("ВведитеID удаляемого контакта:\n");
                scanf("%d", &BUFFINT);
                deleteContact(treeContact, BUFFINT);
                break;
            case 3:
                printf("Введите ID обновляемого контакта:\n");
                scanf("%d", &BUFFINT);
                if(BUFFINT > treeContact->size-1) break;
                cont = searchContact(treeContact->root ,BUFFINT);
                if(!cont) break;
                printf("ID\t|Имя(a)\t|Фамилия(b)\t|Отчество(c)\t|Место_работы(d)\t|Должность(e)\t|Телефон(f)\t|Эл.почта(g)\t|Соцсеть(j)\t|Мессенджер(k) |\n");
                printOneContactAllInfo(cont);
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
                        updateValueForArray(cont, BUFFER, operation, BUFFINT2);
                        break;
                    }
                }
                printf("Введите новое значение поля:\n");
                scanf("%s", BUFFER);
                if(operation == 'a') changeContactName(treeContact, BUFFINT,BUFFER, cont); // это нужно для пересортировки по имени.
                else
                updateContact(cont, BUFFER, operation);
                cont = NULL;
                break;
            case 4:
                printf("%s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "ID", "|Имя","|Фамилия","|Отчество","|Место_работы","|Должность",
                "|Телефон","|Эл.почта","|Соцсеть", "|Мессенджер\n");
                printTreeAllInfo(treeContact->root);
                getc(stdin);
                printf("\n.....Нажмите Enter.....\n");
                getc(stdin);
                break; 
            case 6:
                deleteTree(treeContact->root);
                return 0;
                break; 
            default:
                
        }

    }

}
