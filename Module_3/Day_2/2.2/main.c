#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILENAME "out.txt"
int main(int argc, char *argv[]){
    pid_t pid;
    int pipefd1[2], pipefd2[2];
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1 ) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int N;
    FILE* p; // от потомка к родителю
    FILE* kid; // от родителя к потомку
    FILE* outfile=fopen(FILENAME, "w");
    if(outfile==NULL) {
        perror("file open");
        exit(EXIT_FAILURE);
    }
    if(argc > 1)
        sscanf(argv[1],"%d", &N);
    else exit(-1);
    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            close(pipefd1[0]); // закрываем у потомка дескриптор на чтение
            close(pipefd2[1]); // закрвыаем дескриптор на запись
            p = fdopen(pipefd1[1],"w");
            kid = fdopen(pipefd2[0], "r");
            if(p == NULL || kid == NULL) exit(EXIT_FAILURE);
            int integer;
            for(int i = 0; i < N; i++){
                fprintf(p, "%d\n", rand()%1000); // \n нужно для выгрузки буффера
                fflush(p);
                sleep(1);
                fscanf(kid, "%d", &integer);
                fprintf(outfile, "\t%d\n", integer);   //записываем полученное от родителя сообщение в файл
                fflush(outfile);
            }
            break;
        default:
            close(pipefd1[1]); // закрываем у родителя дескриптор на запись
            p = fdopen(pipefd1[0],"r");
            kid = fdopen(pipefd2[1], "w");
            if(p == NULL || kid == NULL) exit(EXIT_FAILURE);
            int out_integer;
            for(int i = 0; i < N; i++){
                fscanf(p, "%d", &out_integer);
                printf("%d\n", out_integer);
                fprintf(outfile, "%d\n", out_integer);
                fflush(outfile);
                fprintf(kid,"%d\n", out_integer*2);
                fflush(kid);        // сброс буффера
            }

    }
}