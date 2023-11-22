#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
extern void sleep(int);
static int count = 0;

void listener(int sig) {
    switch(sig){
        case SIGINT:
            printf("Пришёл сигнал SIGINT, но я продолжу работу\n");
            break;
        case SIGQUIT:
            printf("Пришёл сигнал SIGQUIT, но я продолжу работу\n");
            break;
    }
}
int main(int argc, char* argv[]){
    FILE* fp = fopen("file.txt", "w");
    if(fp == NULL) {
        printf("File open error\n");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, listener);
    signal(SIGQUIT, listener);
    while(1){
        fprintf(fp, "%d\n", count++);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
    exit(EXIT_SUCCESS);

}