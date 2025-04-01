#include <stdio.h>
#include "01_int_operations.h"

int main() {
    int (*funcs[4])(int, int);
    *funcs=add_int;
    *(funcs+1)=sub_int;
    *(funcs+2)=div_int;
    *(funcs+3)=mul_int;

    int a,b,op;

    printf("Enter numbers: ");
    if(scanf("%d %d", &a, &b)!=2){
        printf("Incorrect input");
        return 1;
    }
    printf("Choose an operation: ");
    if(scanf("%d", &op)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(op<0 || op>3){
        printf("Incorrect input data");
        return 2;
    }
    printf("Result: %d", calculate(a, b, *(funcs+op)));

    return 0;
}
