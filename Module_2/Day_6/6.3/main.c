#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>

#define LEN_OP 25
#define LEN_INFO 250
#define COUNT_OF_OP 6
#define EPSILON 0.001
#define MAX_ITER 10000

#define ERROR -111

#define FILENAME "libmath.so"
#define DIRFUNC "./fun"

typedef struct mathOperation {
    char nameOp[LEN_OP];
    char info[LEN_INFO];
    double (*func)(double, double);
} mathOp;

void addOperation(mathOp* arrOp, double (*func)(double, double), char* nameOp, char* info){
    static int i = 0;
    if(i<COUNT_OF_OP){
        strncpy(arrOp[i].nameOp, nameOp, LEN_OP);
        strncpy(arrOp[i].info, info, LEN_INFO);
        arrOp[i].func = func;
        i++;
    }
}
void printOperation(mathOp* arrOp){
    printf("Доступные операции: \n");
    for(int i = 0; i < COUNT_OF_OP; i++)
    printf("%s (%s)\n", arrOp[i].nameOp, arrOp[i].info);
    printf("Если при выполнении некоторых функций вы получаете необычное значение (%d), "
    "\nто, возможно, введенные вами значения не входят в область сходимости функции\n",ERROR);

}

void readAndAddOp(mathOp* arrOp, void* lib_handler, DIR* dir){
    struct dirent *entry;   // структура, в которую записывается инфа о файлах из dir. например, entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen
    char* error;
    double (*function)(double, double); 
    char* (*infoFunc)(void);
    char funname[LEN_OP], *funinfo = "getInfo";
    char BUFFER[LEN_INFO];
    while ( (entry = readdir(dir)) != NULL) {
        int j = sscanf(entry->d_name, "%[^.]%*[.]%s", funname,BUFFER); // обработка полученной строки из директории
        if (j == 2 && strcmp(BUFFER, "h") == 0){
            //printf("%s %s\n", funname,BUFFER);      
            snprintf(BUFFER, sizeof(BUFFER), "%s%s", funinfo, funname);         // склеиваем строки в буффер

            function = dlsym(lib_handler, funname);
            if ((error = dlerror()) != NULL) {
                    fprintf (stderr, "%s\n", error);
                    continue;
            }

            infoFunc = dlsym(lib_handler,BUFFER);
            if ((error = dlerror()) != NULL) {
                    fprintf (stderr, "%s\n", error);
                    continue;
            }
            addOperation(arrOp, function, funname, infoFunc());
        }
    };
}
void main() {
    mathOp arrOperations[COUNT_OF_OP];
    char operation[LEN_OP];
    double a, b;
    char* error;
    DIR* dir;
    void* library_handler = dlopen(FILENAME,RTLD_LAZY);
    if (!library_handler){
        // если ошибка, то вывести ее на экран
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        exit(1);
    }
    dir = opendir(DIRFUNC);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
    readAndAddOp(arrOperations, library_handler, dir);

    printOperation(arrOperations);
    
    while(1){
        int id_operation = -1;
        printf("Введите, что вы хотите сделать:\n");
        
        scanf("%25s", operation);
        for(int i = 0; i < COUNT_OF_OP; i++)
            if (strcmp (operation, arrOperations[i].nameOp) == 0){
                id_operation = i;
                break;
            }
        if (id_operation == -1){
            printf("Данной функции пока нет в программе\n\n");
            continue;
        }    

        printf("Введите два числа через пробел:\n");
        scanf("%lf %lf",&a,&b);
        fflush(stdin);
        printf("Результат: %g \n\n", arrOperations[id_operation].func(a,b));
        
        }
    }