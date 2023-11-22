#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#define KEY 111
#define MSGSZ 20



typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


int main(int argc, char* argv[])
{
    int msqid;
    key_t key = KEY;
    message_buf rbuf;

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while(1){
        if (msgrcv(msqid, &rbuf, MSGSZ, 0, 0) < 0) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("%s\t%ld\n", rbuf.mtext, rbuf.mtype);
        if(rbuf.mtype == 255) break;
        //sleep(1);
    }
    
    exit(EXIT_SUCCESS);
}