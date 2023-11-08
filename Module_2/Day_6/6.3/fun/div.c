#include "div.h"
double div(double a, double b){
    if(b != 0)
    return a/b;
    else return ERROR;
}
char* getInfodiv(){
	return "Делит одно число на другое - a/b";
}
