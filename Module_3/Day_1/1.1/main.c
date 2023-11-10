#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void done()
{
    printf("ALL DONE; PID: %d\n",getpid());
}
int main(int argc, char* argv[]){
    pid_t pid;
    int rv;
    atexit(done);
    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            printf("CHILD F: %d\n", getpid());
            for(int i = 0; i < argc; i++)
                printf("%s\n", argv[i]);
            exit(EXIT_SUCCESS);
        default:
            
            printf("PARENT F: %d\n", getpid());
            wait(&rv);
            for(int i = 0; i < argc; i++)
                printf("%s\n", argv[i]);
            
            exit(EXIT_SUCCESS);

    }

}