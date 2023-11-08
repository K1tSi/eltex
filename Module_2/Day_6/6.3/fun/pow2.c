#include "pow2.h"
double pow2(double a, double b){
double res = a;
    while(b > 1){
        res*=a;
        b--;
    }
    return res;
}
char* getInfopow2(){
	return "Возводит число (a) в целочисленную степень(b) - a^b";
}
