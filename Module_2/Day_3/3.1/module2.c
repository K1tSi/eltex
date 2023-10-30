#include "module2.h"
#include "module1.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#define LEN_MODE 9
#define COUNT_GROUP 4
#define COUNT_PERM 3

  /*  mode_t    st_mode;         права доступа */
int getPerm(char* filename, char* outInfo){ // 
    struct stat statfile;
    stat(filename, &statfile);
    mode_t mode = statfile.st_mode;
    for(unsigned int i = 0; i < LEN_MODE; i++)
    {
        outInfo[LEN_MODE-i-1] = mode & (1<<i) ? '1' : '0';
    }
    outInfo[LEN_MODE] = '\0';
    return 0;
}

int setPermRWX(char* filename, char* outInfo, char* conditions){ // 
    char buf1[LEN_MODE+1], groups[COUNT_GROUP+1], perms[COUNT_PERM+1], operation[2];
    unsigned char group = 0, perm = 0, op;
    getPerm(filename, buf1);
    sscanf(conditions,"%[agou]%[+-=]%[rwx]",groups, operation, perms);
    //printf("%s %s %s\n", groups, operation, perms);
    for(int i = 0; i< COUNT_GROUP; i++){
        switch(groups[i]){
            case 'a':
                group = 7;
                i = COUNT_GROUP;
                break;
            case 'u':
                group += 4;
                break;
            case 'g':
                group += 2;
                break;
            case 'o':
                group += 1;
                break;
        }
    }
        for(int i = 0; i< COUNT_PERM; i++){
        switch(perms[i]){
            case 'r':
                perm += 4;
                break;
            case 'w':
                perm += 2;
                break;
            case 'x':
                perm += 1;
                break;
        }
    }
    //printf("%d %d %d", group, perm, op);
    switch(operation[0]){
            case '+':
                for(int i = 0; i < LEN_MODE; i++){

                    outInfo[LEN_MODE-i-1] = (1<<((i)/3))&group && 1<<((i)%3)&perm ? '1' : buf1[LEN_MODE-i-1]; // 1<<((i)/3))&group совпадает группа  1<<((i)%3)&perm - совпадают права
                }
                break;
            case '-':
                for(int i = 0; i < LEN_MODE; i++){

                    outInfo[LEN_MODE-i-1] = (1<<((i)/3))&group && 1<<((i)%3)&perm ? '0' : buf1[LEN_MODE-i-1];
                }
                break;
            case '=':
                for(int i = 0; i < LEN_MODE; i++){

                    //outInfo[LEN_MODE-i-1] = (1<<((i)/3))&group && 1<<((i)%3)&perm ? '1' : '0';
                    outInfo[LEN_MODE-i-1] = (1<<((i)/3))&group ? (1<<((i)%3)&perm ? '1':'0') : buf1[LEN_MODE-i-1];  // если подходит по группе, меняем, если нет то оставляем
                }
                break;
    }
        if(group > 7 || perm > 7) return -1;
    
    


}
int setPermOCT(char* filename, char* outInfo, char* conditions){ // 
    char buf1[LEN_MODE+1];
    getPerm(filename, buf1);
    intTobits(conditions, outInfo);
    return 0;

}

/*mode_t is unsigned int
1000000   110110100
#define S_IRWXU 0000700     RWX mask for owner 
#define S_IRUSR 0000400     R for owner 
#define S_IWUSR 0000200    /* W for owner 
#define S_IXUSR 0000100    /* X for owner *

#define S_IRWXG 0000070    /* RWX mask for group 
#define S_IRGRP 0000040    /* R for group *
#define S_IWGRP 0000020    /* W for group *
#define S_IXGRP 0000010    /* X for group *

#define S_IRWXO 0000007    /* RWX mask for other *
#define S_IROTH 0000004    /* R for other *
#define S_IWOTH 0000002    /* W for other *
#define S_IXOTH 0000001    /* X for other *

#define S_ISUID 0004000    /* set user id on execution *
#define S_ISGID 0002000    /* set group id on execution *
#define S_ISVTX 0001000    /* save swapped text even after use *
*/