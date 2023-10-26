#include "module1.h"

int rwxTobits(char* str, char* outStr, int len){

    for(int i = 0; str[i] != '\0'; i ++)
        if(i > len) return -1;
    outStr[len] = '\0';
    for (int i = 0; i < len; i++){
        if(str[i] != '-')
            outStr[i] = '1';
        else outStr[i] = '0';
    }
}
int intTobits(char* str, char* outStr, int len){
    for(int i = 0; str[i] != '\0'; i ++)
        if(i > len) return -1;
    outStr[len] = '\0';

    for (int i = 0, k = 0; i < len; i++){
        char op = str[i];
        op = op - '0';
        for(unsigned char iter = 4; iter != 0; iter >>= 1, k++)
            if(iter & op) outStr[k] = '1';
            else outStr[k] = '0';
    }
}