#include <stdio.h>
#include <stdlib.h>

#include "07_functions.h"

CREATE_READ_FUNCTIONS(int, "%d")
CREATE_SORT_FUNCTIONS(int)
CREATE_DISPLAY_FUNCTIONS(int, "%d")

CREATE_READ_FUNCTIONS(float, "%f")
CREATE_SORT_FUNCTIONS(float)
CREATE_DISPLAY_FUNCTIONS(float, "%f")

CREATE_READ_FUNCTIONS(double, "%lf")
CREATE_SORT_FUNCTIONS(double)
CREATE_DISPLAY_FUNCTIONS(double, "%lf")

int main() {
    int type, size;

    int * array_int;
    float * array_float;
    double * array_double;

    printf("Choose your type: ");
    if(scanf("%d",&type) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(type < 0 || type > 2){
        printf("Incorrect input data");
        return 2;
    }

    printf("Podaj rozmiar tablicy: ");
    if(scanf("%d",&size) != 1){
        printf("Incorrect input");
        return 1;
    }

    if(size < 1){
        printf("Incorrect input data");
        return 2;
    }

    if(type == 0) {
        array_int = calloc(size, sizeof(int));
        if(array_int == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        if(read_int(array_int, size) == 2){
            printf("Incorrect input");
            free(array_int);
            return 1;
        }
        sort_int(array_int, size);
        display_int(array_int, size);
        free(array_int);
    }
    else if(type == 1) {
        array_float = calloc(size, sizeof(float));
        if(array_float == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        if(read_float(array_float, size) == 2){
            printf("Incorrect input");
            free(array_float);
            return 1;
        }
        sort_float(array_float, size);
        display_float(array_float, size);
        free(array_float);
    }
    else if(type == 2) {
        array_double = calloc(size, sizeof(double ));
        if(array_double == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        if(read_double(array_double, size) == 2){
            printf("Incorrect input");
            free(array_double);
            return 1;
        }
        sort_double(array_double, size);
        display_double(array_double, size);
        free(array_double);
    }

    return 0;
}
