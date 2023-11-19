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
    int buffer=1000;
    //srand(time(NULL));
    /*Открываем fifo для чтения и записи*/
    if((fd_fifo=open(TMP_PATH, O_WRONLY | O_NONBLOCK)) == -1){
        fprintf(stderr, "Невозможно открыть fifo\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<COUNT_NUM; i++){
        buffer = rand()%1337;
        write(fd_fifo, &buffer, sizeof(buffer));
    }
    return 0;
}