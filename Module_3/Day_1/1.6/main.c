#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256
char* getModeName(mode_t st_mode);

int printDir(char* dir_name, int num_tab){
    DIR* dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
    char next_dir_name [MAX_PATH];

    struct dirent* entry;
    struct stat statfile;
    while ( (entry = readdir(dir)) != NULL) {
        if(!strcmp(entry->d_name,"..") || !strcmp(entry->d_name,".")) { continue; }
        snprintf(next_dir_name, sizeof(char)*MAX_PATH, "%s/%s", dir_name, entry->d_name);
        int d = stat(next_dir_name, &statfile);
        if(d == -1) continue;
    
        for(int i = 0; i<num_tab; i++) printf("\t"); 
        printf("%s %s %5ld\n",entry->d_name, getModeName(statfile.st_mode), statfile.st_size);
        if(S_ISDIR(statfile.st_mode)){
            
            printDir(next_dir_name, num_tab+1);
        }
    }
    closedir(dir);
}char* getModeName(mode_t st_mode) {
    if(S_ISLNK(st_mode)) return "link" ;   //– символьная ссылка (нет в POSIX.1-1996)
    else if(S_ISREG(st_mode)) return "file";           //– обычный файл
    else if (S_ISDIR(st_mode)) return "dir";            //– каталог
    else if(S_ISCHR(st_mode)) return "chr";               //– символьное устройство
    else if(S_ISBLK(st_mode)) return "blk";          //– блочное устройство
    else if(S_ISFIFO(st_mode)) return "fifo"; //– канал FIFO
    else if(S_ISSOCK(st_mode)) return "socket"; //– сокет
}

int main(){


    printDir(".", 1);
}