#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#define MAX_COUNT_ARG 10
#define MAX_LEN_ARG 50
#define LINE_EXIT "exit"

#define BIN_DIR "/usr/bin/"

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
    str = strtok(buff," \n");        // Выделение первой части строки
    // Выделение последующих частей
    while (str != NULL){
        arg[i] = (char*)malloc(sizeof(char)*MAX_LEN_ARG);
        strncpy(arg[i++], str, MAX_LEN_ARG);
        str = strtok (NULL," \n"); // Выделение очередной части строки
    }
    arg[i]=NULL;
    return arg;
}
int main(int argc, char* argv[]){
    
    pid_t pid;
    int rv;
    double A;
    char BUFFER[MAX_LEN_ARG];
    char PathName[PATH_MAX];
    char** arguments = NULL;
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
                if (execv(arguments[0],arguments) == -1){
                    snprintf(BUFFER, sizeof(char)*MAX_LEN_ARG, "%s%s", BIN_DIR, arguments[0]);         // склеиваем строки в буффер
                    if(getcwd(PathName,PATH_MAX) != NULL){
                        //char *arguments[0] = (char*)malloc(sizeof(char)*PATH_MAX);
                        //free(arguments[0]);
                        //arguments[0] = BUFFER;
                        //snprintf(fiarg, PATH_MAX*sizeof(char) +1, "%s%c%s", PathName,'/', arguments[0]);
                        //arguments++;
                        //printf("%s",arguments[0]);
                        if(execvp(BUFFER,arguments) ==-1) printf("программа не найдена\n");
                        //execlp("/usr/bin/ls","-l",NULL);
                    }
                    

                }
                    
                exit(EXIT_SUCCESS);
            default:
                wait(&rv);
                for(int i = 0; arguments[i] !=NULL; i++)
                    free(arguments[i]);
                if(arguments != NULL) free(arguments);
        }
    }
}
