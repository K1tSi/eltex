#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_COUNT_ARG 10
#define MAX_LEN_ARG 50
#define LINE_EXIT "exit\n"
void done()
{
    printf("Процесс (%d) завершил работу\n",getpid());
}
char** readarg(FILE* fd){       // принимает файловый дескриптор(stdin) и читает оттуда строку с аргументами через пробел
    char buff[MAX_COUNT_ARG*MAX_LEN_ARG];
    char** arg = (char**)malloc(sizeof(char*)*MAX_COUNT_ARG);
    char* str;
    int i = 0;
    fgets(buff,MAX_COUNT_ARG*MAX_LEN_ARG,fd);
    //printf("%s",buff);
    str = strtok(buff," ");        // Выделение первой части строки
    // Выделение последующих частей
    while (str != NULL){
        arg[i] = (char*)malloc(sizeof(char)*MAX_LEN_ARG);
        strncpy(arg[i++], str, MAX_LEN_ARG);
        str = strtok (NULL," "); // Выделение очередной части строки
    }
    arg[i]=NULL;
    return arg;
}
int main(int argc, char* argv[]){
    
    pid_t pid;
    int rv;
    double A;
    char** arguments;
    atexit(done);
    

    while(1){
    printf("Enter prog\n>>>");
    arguments=readarg(stdin);
    if(!strcmp(arguments[0],LINE_EXIT)) exit(EXIT_SUCCESS);
        switch(pid = fork()){
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("Подменяемый процесс: (%d)\n", getpid());
                execv(arguments[0],arguments);

                exit(EXIT_SUCCESS);
            default:
                //fflush(stdin);
                //fflush(stdout);
                wait(&rv);
                
        }
    }
}