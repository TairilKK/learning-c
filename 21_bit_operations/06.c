#include <stdio.h>

#include "06_functions.h"

int main() {
    int type;

    unsigned int a0, b0;
    unsigned int x0;
    unsigned int * px0 = &x0;
    unsigned int *set0 = &a0, *reset0 = &b0;

    unsigned short a1, b1;
    unsigned short x1;
    unsigned short * px1= &x1;
    unsigned short *set1 = &a1, *reset1 = &b1;

    unsigned long a2, b2;
    unsigned long x2;
    unsigned long * px2 = &x2;
    unsigned long *set2 = &a2, *reset2 = &b2;

    printf("Enter data type: \n");
    if(scanf("%d", &type)!= 1){
        printf("Incorrect input");
        return 1;
    }
    if(type<0 || type > 2){
        printf("Incorrect input data");
        return 2;
    }

    printf("Enter an integer number: \n");
    if(type == 0){
        if(scanf("%u", &x0)!= 1){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(x0, set0, reset0);
        printf("%u\n%u\n",*set0, *reset0);
        DISPLAY_BITS(x0);
        REVERSE_BITS(px0);
        DISPLAY_BITS(x0);
    }
    else if(type == 1){
        if(scanf("%hu", &x1)!= 1){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(x1, set1, reset1);
        printf("%hu\n%hu\n",*set1, *reset1);
        DISPLAY_BITS(x1);
        REVERSE_BITS(px1);
        DISPLAY_BITS(x1);
    }
    else {
        if(scanf("%lu", &x2)!= 1){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(x2, set2, reset2);
        printf("%lu\n%lu\n",*set2, *reset2);
        DISPLAY_BITS(x2);
        REVERSE_BITS(px2);
        DISPLAY_BITS(x2);
    }

    return 0;
}
