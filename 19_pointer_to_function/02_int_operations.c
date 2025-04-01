#include <stdio.h>
#include "int_operations.h"

int add_int(int a, int b){
    return a+b;
}
int sub_int(int a, int b){
    return a-b;
}
int div_int(int a, int b){
    if(b==0)
        return 0;
    return a/b;
}
int mul_int(int a, int b){
    return a*b;
}

int (*get_function(enum operations_t operation))(int, int){
    if(operation==op_add)
        return add_int;
    else if(operation==op_sub)
        return sub_int;
    else if(operation==op_div)
        return  div_int;
    else if(operation==op_mul)
        return mul_int;
    return NULL;
}