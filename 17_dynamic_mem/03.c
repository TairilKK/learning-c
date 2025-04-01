#include <stdio.h>

#include "array_2d.h"

int main() {

    /* INPUT */
    int width = 0, height = 0;
    printf("Podaj szerokość i wysokość: ");
    if(scanf(" %d %d", &width, & height) != 2){
        printf("Incorrect input");
        return 1;
    }

    /* CREATE ARRAY 2D */
    int ** array2d = NULL;
    int err = create_array_2d_2(&array2d, width, height);
    if(err == 1){
        printf("Incorrect input data");
        return 2;
    }
    else if(err == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    /* READ ARRAY 2D */
    printf("Podaj liczby: ");
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j){
            if(scanf(" %d", (*(array2d + i) + j)) != 1){
                printf("Incorrect input");
                destroy_array_2d(&array2d, height);
                return 1;
            }
        }

    /* DISPLAY */
    display_array_2d(array2d, width, height);

    /* SUM PRINT */
    for(int i = 0; i < height; printf("%d\n", sum_row(*(array2d + i), width)), ++i);
    printf("%d", sum_array_2d(array2d, width, height));

    /* FREE */
    destroy_array_2d(&array2d, height);

    return 0;
}
