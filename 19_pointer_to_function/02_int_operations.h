//
// Created by jdobr on 05.06.2023.
//

#ifndef INC_01_INT_OPERATIONS_H
#define INC_01_INT_OPERATIONS_H

enum operations_t{
    op_add=0, op_sub, op_div, op_mul
};

int (*get_function(enum operations_t operation))(int, int);
int add_int(int a, int b);
int sub_int(int a, int b);
int div_int(int a, int b);
int mul_int(int a, int b);

#endif //INC_01_INT_OPERATIONS_H
