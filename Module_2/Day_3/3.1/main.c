#include <stdio.h>
#include "module1.h"
int main(){
    char buf[255];
    rwxTobits("r--rw-rwx",buf,9);
    printf("%s\n",buf);
    intTobits("706",buf, 3);
    printf("%s",buf);

}