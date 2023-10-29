#include <stdio.h>
#include <string.h>
#include "module1.h"
#include "module2.h"
#define BUFF_SIZE 255
int main(){
    char buf[BUFF_SIZE], buf1[BUFF_SIZE], buf2[BUFF_SIZE];
    char filename[]= "1_3.h";
    rwxTobits("r--rw-rwx",buf);
    printf("%s\n",buf);

    intTobits("706",buf);
    printf("%s\n",buf);

    getPerm(filename, buf);
    printf("%s\n",buf);

    bitsToint(buf, buf1);
    printf("%s\n",buf1);

    intTobits(buf1,buf);
    printf("%s\n",buf);
    
    bitsTorwx(buf, buf2);
    printf("%s\n",buf2);
    strncpy(buf, "ls -l ", BUFF_SIZE);
    strncat(buf, filename, BUFF_SIZE);
    system(buf);

    setPermRWX(filename, buf2, "a-w");
    printf("%s\n",buf2);

    bitsTorwx(buf2, buf1);
    printf("%s\n",buf1);

    setPermOCT(filename, buf1, "766");
    printf("%s\n",buf1);


    
}