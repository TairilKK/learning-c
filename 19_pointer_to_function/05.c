#include <stdio.h>
#include <stdlib.h>

#include "05_comparators.h"

int main() {

    int (**funcs)(int, int);
    funcs = calloc(4, sizeof(int (*)(int, int)));
    if(funcs == NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    *funcs = comp_int;
    *(funcs+1)= comp_int_abs;
    *(funcs+2)= comp_int_length;
    *(funcs+3)= comp_int_digits_sum;

    int * array;
    int size, operation;

    printf("Podaj długość tablicy: ");
    if(scanf("%d", &size)!=1){
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if(size < 1){
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }

    array = calloc(size, sizeof(int));
    if(array == NULL){
        printf("Failed to allocate memory");
        free(funcs);
        return 8;
    }

    printf("Podaj liczby: ");
    for(int i = 0; i<size; ++i){
        if(scanf("%d", (array + i))!=1){
            printf("Incorrect input");
            free(funcs);
            free(array);
            return 1;
        }
    }


    printf("Podaj rodzaj operacji: ");
    if(scanf("%d", &operation)!=1){
        printf("Incorrect input");
        free(funcs);
        free(array);
        return 1;
    }

    if(operation > 3 || operation < 0) {
        printf("Incorrect input data");
        free(funcs);
        free(array);
        return 2;
    }
    sort_int(array, size, *(funcs + operation));

    for(int i = 0; i<size; printf("%d ", *(array + i)), ++i);

    free(funcs);
    free(array);

    return 0;
}
