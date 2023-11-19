#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "def.h"

int main(int argc, char* argv[]){
    int fd_fifo;
    int buf;
    /*Открываем fifo для чтения и записи*/
    if((fd_fifo=open(TMP_PATH, O_RDONLY)) == -1){
        fprintf(stderr, "Невозможно открыть fifo\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<COUNT_NUM; i++){
        if(read(fd_fifo, &buf, sizeof(buf)) == -1)
            fprintf(stderr, "Невозможно прочесть из FIFO\n");
        else
        printf("Прочитано из FIFO: %d\n",buf);
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}