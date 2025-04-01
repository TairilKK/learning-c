#include <stdio.h>
#include "02_int_operations.h"

int main() {
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
    printf("Result: %d", get_function(op)(a,b));

    return 0;
}
