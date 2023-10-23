#include <stdio.h>

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
double pow2(double a, unsigned int b){
    while(b > 1){
        a*=a;
        b--;
    }
    return a;
}


void main() {
    double a, b;
    char operation;
    printf("Доступные операции: <+>; <->; <:>; <*>; <^>\n"
    "Пример: *\n"
    "a b\n"
    "Результат: a*b\n");
    while(1){
        printf("Введите, что вы хотите сделать:\n");
        
        //

        operation = getchar();
        while(operation=='\n') operation = getchar();
        //scanf("%c", &operation);
        printf("Введите два числа через пробел:\n");
        scanf("%lf %lf",&a,&b);
        fflush(stdin);
        switch(operation){
        case '+': 
            printf("Результат: %g \n\n", sum(a,b));
            break;
        case '-': 
            printf("Результат: %g \n\n", sum(a,-b));
            break;
        case ':':
            printf("Результат: %g \n\n", div(a,b)); 
            break;
        case '*': 
            printf("Результат: %g \n\n", mult(a,b));
            break;
        case '^': 
            printf("Результат: %g \n\n", pow2(a,b));
            break;
        default:
            printf("Введена несуществующая операция, попробуйте снова\n\n");
        }
    }
}