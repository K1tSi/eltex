#include <stdio.h>
#include <string.h>

#define LEN_OP 25
#define LEN_INFO 250
#define COUNT_OF_OP 6
#define EPSILON 0.001
#define MAX_ITER 10000

#define ERROR -111
typedef struct mathOperation {
    char nameOp[LEN_OP];
    char info[LEN_INFO];
    double (*func)(double, double);
} mathOp;
double sum(double a, double b){
    return a+b;
}
double div(double a, double b){
    if(b != 0)
    return a/b;
    else return -0;
}
double mult(double a, double b){
    return a*b;
}
double pow2(double a, double b){
    while(b > 1){
        a*=a;
        b--;
    }
    return a;
}
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

void addOperation(mathOp* arrOp, double (*func)(double, double), char* nameOp, char* info){
    static int i = 0;
    if(i<COUNT_OF_OP){
        strncpy(arrOp[i].nameOp, nameOp, LEN_OP);
        strncpy(arrOp[i].info, info, LEN_INFO);
        arrOp[i].func = func;
        i++;
    }
}
void printOperation(mathOp* arrOp){
    printf("Доступные операции: \n");
    for(int i = 0; i < COUNT_OF_OP; i++)
    printf("%s (%s)\n", arrOp[i].nameOp, arrOp[i].info);
    printf("Если при выполнении некоторых функций вы получаете необычное значение (%d), "
    "\nто, возможно, введенные вами значения не входят в область сходимости функции\n",ERROR);

}

void main() {
    mathOp arrOperations[COUNT_OF_OP];
    char operation[LEN_OP];
    double a, b;

    addOperation(arrOperations, sum, "sum","Суммирует два числа - a+b");
    addOperation(arrOperations, div, "div","Делит одно число на другое - a/b");
    addOperation(arrOperations, mult, "mult","Умножает два числа - a*b");
    addOperation(arrOperations, pow2, "pow","Возводит число (a) в целочисленную степень(b) - a^b");
    addOperation(arrOperations, cos2, "cos","Косинус числа (b) умноженный на число (a) - a*cos(b)");
    addOperation(arrOperations, arctg2,"arctg", "Арктангенс числа (b) умноженный на число (a) - a*arctg(b)");

    printOperation(arrOperations);
    
    while(1){
        int id_operation = -1;
        printf("Введите, что вы хотите сделать:\n");
        
        scanf("%25s", operation);
        for(int i = 0; i < COUNT_OF_OP; i++)
            if (strcmp (operation, arrOperations[i].nameOp) == 0){
                id_operation = i;
                break;
            }
        if (id_operation == -1){
            printf("Данной функции пока нет в программе\n\n");
            continue;
        }    
            

        printf("Введите два числа через пробел:\n");
        scanf("%lf %lf",&a,&b);
        fflush(stdin);
        printf("Результат: %g \n\n", arrOperations[id_operation].func(a,b));
        
        }
    }