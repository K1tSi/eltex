#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
extern void sleep(int);
static int wait = 3;
int count = 0;

void listener(int sig) {
    wait--;
    if(wait)
    printf("До выключения осталось (%d) сигнала\n", wait);
    else printf("Завершение работы...\n");
}
int main(int argc, char* argv[]){
    FILE* fp = fopen("file.txt", "w");
    if(fp == NULL) {
        printf("File open error\n");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, listener);
    while(wait){
        fprintf(fp, "%d\n", count++);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
    exit(EXIT_SUCCESS);

}