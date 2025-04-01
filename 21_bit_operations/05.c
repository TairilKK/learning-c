#include <stdio.h>
#include "05_functions.h"

int main() {
    int type;
    int ai, bi;
    float af, bf;
    printf("Enter data type: ");
    if(scanf("%d", &type)!=1){
        printf("Incorrect input");
        return 1;
    }

    if(type == 0){
        printf("Enter numbers: ");
        if(scanf("%d %d", &ai, &bi)!=2){
            printf("Incorrect input");
            return 1;
        }
    }
    else if(type == 1){
        printf("Enter numbers: ");
        if(scanf("%f %f", &af, &bf)!=2){
            printf("Incorrect input");
            return 1;
        }
    }
    else{
        printf("incorrect input data");
        return 2;
    }

    if(type == 0)
        printf("%d\n%d\n%d\n%d", SQR(ai), SQR(bi), MAX(ai, bi), MIN(ai,bi));
    else
        printf("%f\n%f\n%f\n%f", SQR(af), SQR(bf), MAX(af, bf), MIN(af,bf));

    return 0;
}
