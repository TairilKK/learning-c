#include <stdio.h>
#include "for_loop.h"

void for_loop(double start, double step, double end, void(*func)(double)){
    if(func==NULL || step==0)
        return;
    if(start>=end && step > 0)
        return;
    if(start<=end && step < 0)
        return;

    func(start);
    start+=step;
    for_loop(start, step, end, func);
}

void print_value(double a){
    printf("%lf ", a);

}

void print_accumulated(double a){
    static double st = 0;
    st+=a;
    printf("%lf ", st);
}

void print_square(double a){
    printf("%lf ", a*a);
}

void print_abs(double a){
    if(a<0)
        a=-a;
    printf("%lf ", a);
}
