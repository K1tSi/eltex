#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MASK_LEN 32
#define LEN_IP 16
#define COUNT_OCT 4


int stringToIP(char* str){      // принимает строку вида "255.255.123.1", возвращает айпи в виде инта
    int oct1, oct2, oct3, oct4;
    sscanf(str, "%d.%d.%d.%d", &oct1,&oct2,&oct3,&oct4);
    int IP = (oct1<<24) + (oct2<<16) + (oct3<<8) + oct4;
    //printf("IP:%x\n", IP);
    return IP;
}
int intToMask(int countBit){       // принимает число до 32, возвращает маску 
    int mask = 0;
    for(int i = 1; i <= countBit; i++){
        mask += 1<<(MASK_LEN-i);
    }
    //printf("Mask:%x\n", mask);
    return mask;
}
int inSubnet(int sourceIpAddress, int mask, int distIpAddress){     // принимает исходный адрес, маску и адрес отправления; возвращает 1 если ip из одной подсети
    int sourseSubnet = sourceIpAddress&mask; // побитовое умножение
    int distSubnet = distIpAddress&mask;

    return !(distSubnet^sourseSubnet);
}
void ipToString(int IP, char* pstring){ // преобразование числового айпи в строку
    unsigned char str[LEN_IP+1]; // перевёрнутая строка
    unsigned char str2[LEN_IP+1]; // нормальная строка с айпи
    unsigned char octet = 0;
    int place_int = 0;
    for(int i = 0; i < COUNT_OCT; i++){
        int newIP = IP >> 8*i;

        octet = (unsigned char) newIP; // записываем младшие 8 бит айпи
        do
        {
            str[place_int] = octet%10 + '0';
            place_int++;
            octet = octet/10;
        } while (octet > 0);
        str[place_int] = '.';
        place_int++;
    }
    str[place_int] = '\0';
    for(int i = 0; i < place_int; i++) // переворачиваем строку
        str2[i] = str[place_int-i-2];
    
    str2[place_int] = '\0';

    strncpy(pstring, str2, place_int);
    //printf("%s",str2);

}
int main(int argс, char* argv[]){   // принимаемый формат ./main 168.34.12.1 /16 1000
    srand(time(NULL));
    char BUFFER_IP[LEN_IP+1];
    int countBit;
    int N,count=0;
    int IP = stringToIP(argv[1]);
    int distIP = rand();
    sscanf(argv[2], "/%d", &countBit);
    sscanf(argv[3], "%d", &N);
    if(countBit > MASK_LEN || countBit < 0) {
        printf("Неверная маска\n");
        return -11;
    }
    int mask = intToMask(countBit);
    for(int i = 0; i < N; i++){
        distIP = rand();
        //ipToString(distIP,BUFFER_IP);
        //printf("\n%s",BUFFER_IP);
        if (inSubnet(IP,mask, distIP)){
            //ipToString(distIP,BUFFER_IP); // для того, чтобы выводил айпишники, нужно снять комментарии
            //printf("%s\n",BUFFER_IP);
            count++;
        }
    }
    ipToString(distIP,BUFFER_IP);
    printf("Last dist IP generate: (%s)\n",BUFFER_IP);
    printf("Paсkаge in subnet: %g %%\n", (double)count*100/N);
}