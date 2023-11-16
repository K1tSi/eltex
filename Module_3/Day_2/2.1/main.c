#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILENAME "out.txt"
int main(int argc, char *argv[]){
    pid_t pid;
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int N;
    FILE* p;
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
            close(pipefd[0]); // закрываем у потомка дескриптор на чтение
            p = fdopen(pipefd[1],"w");
            for(int i = 0; i < N; i++){
                fprintf(p, "%d\n", rand()%1000); // \n нужно для выгрузки буффера
                fflush(p);
                sleep(1);
            }
            break;
        default:
            close(pipefd[1]); // закрываем у родителя дескриптор на запись
            p = fdopen(pipefd[0],"r");
            int out_integer;
            for(int i = 0; i < N; i++){
                fscanf(p, "%d", &out_integer);
                printf("%d\n", out_integer);
                fprintf(outfile, "%d\n", out_integer);
                fflush(outfile);
            }

    }
}