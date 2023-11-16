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

char** strArgTochar(char* arguments, char* deli){       // принимает строку, которую нужно разбить на строки по разделителям из deli
    char** arg = (char**)malloc(sizeof(char*)*MAX_COUNT_ARG);
    char* str;
    int i = 0;
    str = strtok(arguments, deli);        // Выделение первой части строки
    // Выделение последующих частей
    while (str != NULL){
        arg[i] = (char*)malloc(sizeof(char)*MAX_LEN_ARG);
        strncpy(arg[i++], str, MAX_LEN_ARG);
        str = strtok (NULL, deli); // Выделение очередной части строки
    }
    arg[i]=NULL;
    return arg;
}
char** readargNew(FILE* fd){
    char buff[MAX_COUNT_ARG*MAX_LEN_ARG];
    fgets(buff,MAX_COUNT_ARG*MAX_LEN_ARG,fd);
    return strArgTochar(buff, " \n");
}

int forking(char*** arguments, int num){
    if(arguments[num]==NULL) return 0;
    char BUFFER[MAX_LEN_ARG];
    pid_t pid;
    int rv;
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    switch(pid = fork()){
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("Подменяемый процесс: (%d)\n", getpid());
                // подмена ввода вывода
                close(pipefd[0]);
                if(arguments[num+1] != NULL) // для последней команды сохраняем стандартный вывод
                    if(dup2(pipefd[1], 1) == -1) exit(EXIT_FAILURE);

                if (execv(arguments[num][0],arguments[num]) == -1){
                    snprintf(BUFFER, sizeof(char)*MAX_LEN_ARG, "%s%s", BIN_DIR, arguments[num][0]);         // склеиваем строки в буффер
                    if(execvp(BUFFER,arguments[num]) ==-1) perror("программа не найдена\n");
                }
                exit(EXIT_SUCCESS);
            default:
                close(pipefd[1]);
                if(dup2(pipefd[0], 0) == -1) exit(EXIT_FAILURE);
                forking(arguments, num+1);
                wait(&rv);
        }
}

int main(int argc, char* argv[]){
    
    int count_arg, current_arg = 0, iter;
    char BUFFER2[MAX_COUNT_ARG*MAX_LEN_ARG];
    char*** arguments = NULL;   // разделение разных комманд и их аргументов по разным массивам указателей на строки
    char** commands = NULL;
    atexit(done);
    int fdout = dup(0), fdin = dup(1);      // ассоциируем со стандартными потоками ещё пару дескр. так как в конвеере они меняются
    if(fdout == -1 || fdin == -1) exit(EXIT_FAILURE);
    while(1){
    
    printf("Enter prog\n>>>");
    fgets(BUFFER2,MAX_COUNT_ARG*MAX_LEN_ARG,stdin);
    commands = strArgTochar(BUFFER2, "|");  // делим исходную строку на разные команды
    for(count_arg = 0; commands[count_arg] != NULL; count_arg++);
    arguments = (char***)malloc(sizeof(char**)*(count_arg+1));
    for(iter = 0; iter < count_arg; iter++){
        arguments[iter] = strArgTochar(commands[iter]," \n");
    }
    arguments[iter++] = NULL;
    for(int i = 0; i < count_arg; i++) {
        for(int j = 0; arguments[i][j]!=NULL; j++){
            printf("%s ", arguments[i][j]);
        }
        printf("\n");
    }
    if(!strcmp(arguments[0][0],LINE_EXIT)) exit(EXIT_SUCCESS);
    //sleep(1);
    forking(arguments, 0);
    dup2(fdout, 0);
    dup2(fdin, 1);
    for(int i = 0; arguments[i] !=NULL; i++){
            for(int j = 0; arguments[i][j]!=NULL; j++)
                free(arguments[i][j]);
            free(arguments[i]);
    }
    if(arguments != NULL) free(arguments);
    for(int i = 0; commands[i] != NULL; i++){
            free(commands[i]);
    }
    if(commands!= NULL) free(commands);
    arguments = NULL;
    commands = NULL;
    }
}
