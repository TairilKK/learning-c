//
// Created by jdobr on 05.06.2023.
//

#include <stdio.h>
#include "06_comparators.h"

/*
int comp_int(const int *a, const int *b){
    if((*a)>(*b))
        return 1;
    else if((*a)<(*b))
        return -1;
    else
        return 0;
}
int comp_double(const double *a, const double *b){
    if((*a)>(*b))
        return 1;
    else if((*a)<(*b))
        return -1;
    else
        return 0;
}

int comp_point(const struct point_t *a, const struct point_t *b){
    if (a->x > b->x)
        return 1;
    else if (a->x < b->x)
        return -1;
    if(a->y > b->y)
        return 1;
    else if(a->y < b->y)
        return -1;
    return 0;
}
*/

int comp_int(const void *a, const void *b) {
    if(a == NULL || b == NULL)
        return -22;

    const int *ia = (const int *)a;
    const int *ib = (const int *)b;

    if(*ia > *ib)
        return 1;
    else if(*ia < *ib)
        return -1;
    else
        return 0;
}

int comp_double(const void *a, const void *b){
    if(a == NULL || b == NULL)
        return -22;
    const double *da = (const double *)a;
    const double *db = (const double *)b;

    if(*da > *db)
        return 1;
    else if(*da < *db)
        return -1;
    else
        return 0;
}

int comp_point(const void *a, const void *b) {
    if(a == NULL || b == NULL)
        return -22;

    const struct point_t *pa = (const struct point_t *)a;
    const struct point_t *pb = (const struct point_t *)b;

    if (pa->x > pb->x)
        return 1;
    else if (pa->x < pb->x)
        return -1;

    if(pa->y > pb->y)
        return 1;
    else if(pa->y < pb->y)
        return -1;

    return 0;
}


void swap(void* a, void* b, int element_size) {
    char* a_ptr = (char*)a;
    char* b_ptr = (char*)b;
    char temp;

    for (int i = 0; i < element_size; i++) {
        temp = *(a_ptr + i);
        *(a_ptr + i) = *(b_ptr + i);
        *(b_ptr + i) = temp;
    }
}

int sort(void* array, int array_size, int element_size, int(*func)(const void*, const void*)) {
    if(array == NULL || func == NULL || array_size < 1 || element_size <= 0)
        return 1;

    for (int i = 0; i < array_size - 1; i++) {
        for (int j = 0; j < array_size - i - 1; j++) {
            if (func((char*)array + j * element_size, (char*)array + (j + 1) * element_size) > 0) {
                swap((char*)array + j * element_size, (char*)array + (j + 1) * element_size, element_size);
            }
        }
    }
    return 0;
}
