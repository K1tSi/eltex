#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void done()
{
    printf("Процесс под номером (%d) завершил работу\n",getpid());
}
int main(int argc, char* argv[]){
    pid_t pid;
    int rv;
    double A;
    atexit(done);
    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            printf("Дочерний процесс: (%d)\n", getpid());
            for(int i = argc/2 + 1; i < argc; i++){ 
                if(sscanf(argv[i],"%lf",&A))
                    printf("S%d: %g\n", i, A*A);
            }
            exit(EXIT_SUCCESS);
        default:
            printf("Родительский процесс (%d)\n", getpid());

            for(int i = 1; i <= argc/2; i++){ 
                if(sscanf(argv[i],"%lf",&A))
                    printf("S%d: %g\n", i, A*A);
            }
            wait(&rv);
            exit(EXIT_SUCCESS);
            
    }

}