#include "module1.h"
#define LEN_MODE_BIT 9
#define LEN_MODE_OCT 3
int rwxTobits(char* str, char* outStr){

    for(int i = 0; str[i] != '\0'; i ++)    // проверка на соответствие длине прав rwxrwxrwx - 9
        if(i > LEN_MODE_BIT) return -1;
    for (int i = 0; i < LEN_MODE_BIT; i++){      // если встречается '-' то 0, иначе
        if(str[i] != '-' && (str[i] == 'r' || str[i] == 'w' || str[i] == 'x'))
            outStr[i] = '1';
        else outStr[i] = '0';
    }
    outStr[LEN_MODE_BIT] = '\0';             // конец строки
    return 0;
}

int bitsTorwx(char* str, char* outStr){

    for(int i = 0; str[i] != '\0'; i ++)    
        if(i > LEN_MODE_BIT) return -1;

    for (int i = 0; i < LEN_MODE_BIT; i++){      
        if(str[i] == '1')
            outStr[i] = i%3==0 ? 'r' : i%3==1 ? 'w' : 'x';
        else outStr[i] = '-';
    }
    outStr[LEN_MODE_BIT] = '\0';    
    return 0;
}

int intTobits(char* str, char* outStr){
    for(int i = 0; str[i] != '\0'; i ++)
        if(i > LEN_MODE_OCT) return -1;

    for (int i = 0, k = 0; i < LEN_MODE_OCT; i++){
        char op = str[i];
        op = op - '0';
        for(unsigned char iter = 4; iter != 0; iter >>= 1, k++)
            if(iter & op) outStr[k] = '1';
            else outStr[k] = '0';
    }
    outStr[LEN_MODE_BIT] = '\0';         // установка нулевого символа
    return 0;
}

int bitsToint(char* str, char* outStr){
    for(int i = 0; str[i] != '\0'; i ++)
        if(i > LEN_MODE_BIT) return -1;

    for(int i = 0; i < LEN_MODE_OCT; i++)
        outStr[i] = '0';
    
    for (int i = 0; i < LEN_MODE_BIT; i++){
        char op = str[i];
        op = op - '0';
        outStr[i/LEN_MODE_OCT] += op << (LEN_MODE_OCT-1-i%LEN_MODE_OCT);
    }
    outStr[LEN_MODE_OCT] = '\0';         // установка нулевого символа
    return 0;
}