#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KEY 111
#define MSGSZ 20

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

int main(int argc, char* argv[])
{
    int msqid;  // айди очереди
    int msgflg = IPC_CREAT | 0666;
    key_t key = KEY;
    message_buf sbuf;
    size_t buf_length;

    if ((msqid = msgget(key, msgflg)) < 0) {
        perror("msggett");
        exit(EXIT_FAILURE);
    }
    else 
     printf("succeeded: msqid = %d\n", msqid);


    //strcpy(sbuf.mtext, "I am in the queue?");
    
    
    while(1){
        sbuf.mtype = 200 + rand()%56;
        for(int i = 0; i<MSGSZ-1; i++){
            sbuf.mtext[i] = 33 + rand()%90; 
            }
        sbuf.mtext[MSGSZ-1] = '\0';
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            printf ("%d, %ld, %s, %ld\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        else 
            printf("M: \"%s\" Sent\t t:%ld\n ", sbuf.mtext, sbuf.mtype);
        if(sbuf.mtype == 255) break;
        //sleep(1);
    }
        
    exit(EXIT_SUCCESS);
}