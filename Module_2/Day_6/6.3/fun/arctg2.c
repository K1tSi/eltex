#include "arctg2.h"
//x -  x^3^/3 + x^5^/5 +...+ (-1)^n+1^x^2n-1^/(2n-1)
double arctg2(double a, double b){
    double eps = EPSILON;
    double iter = b;
    double result = 0;
    result += iter;
    if(b*b > 1.0001) return ERROR; 
    for(int i = 3; i< MAX_ITER; i+=2){
        iter = (-1)*(iter*b*b)/(i);
        result += iter;
        if(iter*iter < eps*eps) break;
    }
    return a*result;
}
char* getInfoarctg2(){
	return "Арктангенс числа (b) умноженный на число (a) - a*arctg(b)";
}

