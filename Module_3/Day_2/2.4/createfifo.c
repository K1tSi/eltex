#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "def.h"
int main(){
        unlink(TMP_PATH);
    if((mkfifo(TMP_PATH, O_RDWR | S_IRWXO | S_IRWXG | S_IRWXU)) == -1){
        fprintf(stderr, "Невозможно создать fifo");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}