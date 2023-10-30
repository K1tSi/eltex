#include <stdio.h>
#include <string.h>
#include "module1.h"
#include "module2.h"
#define BUFF_SIZE 255
int main(){
    char buf[BUFF_SIZE], buf1[BUFF_SIZE], buf2[BUFF_SIZE],buf3[BUFF_SIZE];

    char filename1[BUFF_SIZE];
    /*char filename[BUFF_SIZE]= "1_3.h";

    rwxTobits("r--rw-rwx",buf);
    printf("%s\n",buf);

    intTobits("706",buf);
    printf("%s\n",buf);

    getPerm(filename, buf);
    printf("%s\n",buf);

    bitsToint(buf, buf1);
    printf("%s\n",buf1);

    intTobits(buf1,buf);
    printf("%s\n",buf);
    
    bitsTorwx(buf, buf2);
    printf("%s\n",buf2);
    strncpy(buf, "ls -l ", BUFF_SIZE);
    strncat(buf, filename, BUFF_SIZE);
    system(buf);

    setPermRWX(filename, buf2, "a-w");
    printf("%s\n",buf2);

    bitsTorwx(buf2, buf1);
    printf("%s\n",buf1);

    setPermOCT(filename, buf1, "766");
    printf("%s\n",buf1);*/
    int op = 0, op1 = 0;
    printf("Привет, это программа по 1 заданию третьего дня в школе Элтекс\n");
    while(1){
        printf("\nПожалуйста, выбери какой пункт программы ты хочешь протестировать:\n"
        "\t1. Преобразование буквенной(rwxrw-rw-) или восьмеричной(766) записи прав доступа в двоичную(111110110)\n"
        "\t2. Получение прав доступа определённого файла\n"
        "\t3. Изменение прав доступа(фиктивное) для файла аналогично chmod\n"
        "\t0. Выход из программы\n"
        "Введите номер пункта: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Введите 1, если хотите преобразовать буквенную запись, 2 если восьмеричную\n");
                scanf("%d", &op1);
                if(op1 == 1){
                printf("Отлично! Теперь введите буквенную запись (Пример rwxrw-rw-)\n");
                scanf("%s", buf);
                rwxTobits(buf,buf1);
                printf("Права (%s) в битовом представлении выглядят так:\n%s\n",buf,buf1);

                }
                else if(op1 == 2){
                printf("Отлично! Теперь введите числовую запись (Пример 766)\n");
                scanf("%s", buf);
                intTobits(buf,buf1);
                printf("Права (%s) в битовом представлении выглядят так:\n%s\n",buf,buf1);
                }
                break;
            case 2:
                printf("Введите имя файла (Например: main.c)\n");
                scanf("%s", filename1);

                getPerm(filename1, buf);
                bitsToint(buf, buf1);
                bitsTorwx(buf, buf2);
                printf("Права доступа к файлу(%s): \n\tбитовое представление (%s)\n\tчисленное представление (%s)\n\tбуквенное представление (%s)\n",filename1,buf,buf1,buf2);
                buf[0] = '\0', buf1[0] = '\0', buf2[0] = '\0';
                break;
            case 3:
                printf("Введите имя файла (Например: main.c)\n");
                scanf("%s", filename1);
                getPerm(filename1, buf);
                bitsToint(buf, buf1);
                bitsTorwx(buf, buf2);
                printf("Текущие прова доступа к файлу(%s): \n\tбитовое представление (%s)\n\tчисленное представление (%s)\n\tбуквенное представление (%s)\n",filename1,buf,buf1,buf2);
                buf[0] = '\0', buf1[0] = '\0', buf2[0] = '\0';

                printf("Введите 1, если хотите использовать буквенную установку прав, 2 если восьмеричную\n");
                scanf("%d", &op1);
                if(op1 == 1){
                printf("Отлично! Теперь введите буквенную установку прав (Пример a+rwx)\n");
                scanf("%s", buf);
                setPermRWX(filename1, buf1, buf);

                }
                else if(op1 == 2){
                printf("Отлично! Теперь введите числовую запись прав (Пример 766)\n");
                scanf("%s", buf);
                setPermOCT(filename1, buf1, buf);
                }
                bitsTorwx(buf1,buf2);
                bitsToint(buf1,buf3);
                printf("Права доступа к файлу(%s) были изменены на:\n\tбитовое представление (%s)\n\tчисленное представление (%s)\n\tбуквенное представление (%s)\n",filename1,buf1,buf2,buf3);
                break;
            
        }
        if(!op) break;
    }

    
}