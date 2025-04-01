//
// Created by jdobr on 31.08.2023.
//

#include <stdarg.h>


#include "06_function.h"

unsigned long long power(unsigned long long a, int n){
    if (n < 0) return 1ull;
    unsigned long long res = 1;
    for(int i = 1; i < n; ++i)
        res *= a;
    return res;
}

unsigned long long bits_to_number(int * err_code, int n, ...){
    if(n < 1 || n > 64){if(err_code) *err_code = 1; return 0;}
    if(err_code) *err_code = 0;

    unsigned long long  res = 0;
    va_list vaList;
    va_start(vaList, n);
    unsigned long long arg;
    for(int i = 0; i < n; ++i){

        if((arg = va_arg(vaList, unsigned long long)) == 1ull)
            res += power(2, n - i);
        else if(arg != 0){
            if(err_code) *err_code = 1;
            va_end(vaList);
            return 0;
        }
    }
    va_end(vaList);
    return res;
}
