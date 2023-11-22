#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int count = 0;
int main(int argc, char* argv[]){
    FILE* fp = fopen("file.txt", "w");
    if(fp == NULL) {
        printf("File open error\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        fprintf(fp, "%d\n", count++);
        fflush(fp);
        sleep(1);
    }

}