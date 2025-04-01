//
// Created by jdobr on 09.08.2023.
//

#ifndef INC_06_COMPARATORS_H
#define INC_06_COMPARATORS_H

int comp_int(int a, int b);
int comp_int_abs(int a, int b);
int comp_int_length(int a, int b);
int comp_int_digits_sum(int a, int b);

int sort_int(int * array, int size, int (*func)(int, int));

#endif //INC_06_COMPARATORS_H
