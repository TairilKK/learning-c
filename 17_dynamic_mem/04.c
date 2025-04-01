#include <stdio.h>

#include "matrix.h"


int main() {
    struct matrix_t m;
    int w, h;

    printf("Podaj szerokość i wysokość: ");
    if(scanf(" %d %d", &w, &h) != 2){
        printf("incorrect input");
        return 1;
    }
    if(w < 1 || h < 1){
        printf("incorrect input data");
        return 2;
    }

    if(matrix_create(&m, w, h) != 0){
        printf("Failed to allocate memory");
        return 8;
    }
    if(matrix_read(&m) == 2){
        matrix_destroy(&m);
        printf("incorrect input");
        return 1;
    }

    matrix_display(&m);
    matrix_destroy(&m);

    return 0;
}
