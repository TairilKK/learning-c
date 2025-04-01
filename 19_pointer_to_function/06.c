#include <stdio.h>
#include <stdlib.h>
#include "06_comparators.h"

int main() {

    int data_type;
    int array_size;

    int * array_int;
    double * array_double;
    struct point_t * array_point_t;

    printf("Enter data type: ");

    if(scanf("%d", &data_type) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(data_type<0 || data_type>2){
        printf("Incorrect input data");
        return 1;
    }

    printf("Enter array size: ");
    if(scanf("%d", &array_size) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(array_size <= 0){
        printf("Incorrect input data");
        return 2;
    }

    if(data_type == 0){

        array_int = (int *) calloc(array_size, sizeof (int));
        if(array_int == NULL){
            printf("Failed to allocate memory");
            return 8;
        }

        printf("Enter ints:\n");
        for(int i = 0; i<array_size; ++i)
            if(scanf("%d", (array_int + i)) != 1){
                printf("Incorrect input");
                free(array_int);
                return 1;
            }

        sort(array_int, array_size, sizeof(int), comp_int);

        for(int i = 0; i<array_size; ++i)
            printf("%d ", *(array_int + i));

        free(array_int);
    }

    else if(data_type == 1){

        array_double = (double *) calloc(array_size, sizeof (double));
        if(array_double == NULL){
            printf("Failed to allocate memory");
            return 8;
        }

        printf("Enter doubles:\n");
        for(int i = 0; i<array_size; ++i)
            if(scanf("%lf", (array_double + i)) != 1){
                printf("Incorrect input");
                free(array_double);
                return 1;
            }

        sort(array_double, array_size, sizeof(double), comp_double);

        for(int i = 0; i<array_size; ++i)
            printf("%lf ", *(array_double + i));

        free(array_double);
    }
    else if(data_type == 2){

        array_point_t = (struct point_t *) calloc(array_size, sizeof (struct point_t));
        if(array_point_t == NULL){
            printf("Failed to allocate memory");
            return 8;
        }

        printf("Enter points:\n");
        for(int i = 0; i<array_size; ++i)
            if(scanf("%lf %lf", &((array_point_t + i)->x), &((array_point_t + i)->y) ) != 2){
                printf("Incorrect input");
                free(array_point_t);
                return 1;
            }

        sort(array_point_t, array_size, sizeof(struct point_t), comp_point);

        for(int i = 0; i<array_size; ++i)
            printf("%lf %lf\n", ((array_point_t + i)->x), ((array_point_t + i)->y));

        free(array_point_t);
    }

    return 0;
}
