#include <stdio.h>

#include "comparators.h"

int comp_int(int a, int b){
    return a-b;
}


int comp_int_abs(int a, int b){
    if(a<0)
        a*=-1;

    if(b<0)
        b*=-1;

    return a-b;
}

int comp_int_length(int a, int b){
    int la = 0, lb = 0;

    while(a!=0) {
        a /= 10;
        la++;
    }


    while(b!=0) {
        b /= 10;
        lb++;
    }

    return la - lb;
}

int comp_int_digits_sum(int a, int b){
    int la = 0,da , lb = 0, db;

    while(a!=0) {
        da = a%10;
        if(da<0)
            da*=-1;
        la += da;
        a /= 10;
    }


    while(b!=0) {
        db = b%10;
        if(db<0)
            db*=-1;

        lb += db;
        b /= 10;
    }

    return la - lb;
}

int sort_int(int * array, int size, int (*func)(int, int)){
    if(array == NULL || func == NULL || size < 1)
        return 1;
    int temp;

    for(int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (func(*(array + j), *(array + j + 1)) > 0) {
                temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
    return 0;
}
