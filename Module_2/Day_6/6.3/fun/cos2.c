#include "cos2.h"
//1 - x^2/ 2! + x^4/4! + ...+ (-1)^n x^2n/(2n)!	cos(x)
double cos2(double a, double b){
    double eps = EPSILON;
    double iter = (-1)*b*b/2;
    double result = 1;
    result += iter;
    if(b*b > 144) return ERROR; 
    for(int i = 3; i< MAX_ITER; i+=2){
        iter = (-1)*(iter*b*b)/(i*(i+1));
        result += iter;
        if(iter*iter < eps*eps) break;
    }
    return result;
}
char* getInfocos2(){
	return "Косинус числа (b) умноженный на число (a) - a*cos(b)";
}

