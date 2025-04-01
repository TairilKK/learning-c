#include <stdio.h>
#include <stdlib.h>
#include "03_for_loop.h"

int main() {
    double start = 0, step = 10, end = 40;
    int op;
    void (**funcs)(double);
    funcs = calloc(4,sizeof(void(*)(double)));
    *funcs=print_value;
    *(funcs+1)=print_accumulated;
    *(funcs+2)=print_square;
    *(funcs+3)=print_abs;

    printf("Podaj poczatek, krok i koniec przedzialu: ");
    if(scanf("%lf %lf %lf", &start, &step, &end) != 3){
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if((start>=end && step > 0)||(start<=end && step < 0) || step==0){
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }

    printf("Podaj rodzaj operacji: ");
    if(scanf("%d", &op)!=1){
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if(op<0||op>3){
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }
    for_loop(start, step, end, *(funcs + op));
    free(funcs);
    return 0;
}
