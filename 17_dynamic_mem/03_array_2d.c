//
// Created by jdobr on 24.08.2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "03_array_2d.h"


int create_array_2d_2(int ***ptr, int width, int height){
    if(!ptr || width < 1 || height < 1) return 1;

    *ptr = (int **)calloc(height, sizeof (int *));
    if(!(*ptr)) return 2;

    for(int i = 0; i < height; ++i){
        *(*ptr + i) = (int *)calloc(width, sizeof (int));
        if(!(*(*ptr + i))){
            destroy_array_2d(ptr, height);
            return 2;
        }
    }
    return 0;
}

void destroy_array_2d(int ***ptr, int height){
    if(!ptr || !(*ptr) || height < 1) return;
    for(int i = 0; i < height; free(*((*ptr) + i)),++i);
    free(*ptr);
    *ptr = NULL;
}

void display_array_2d(int **ptr, int width, int height){
    if(!ptr || !(*ptr) || height < 1 || width < 1) return;

    for(int i = 0; i < height; printf("\n"), ++i)
        for(int j = 0; j < width; printf("%d ",*(*(ptr + i) + j)), ++j);
}

int sum_array_2d(int **ptr, int width, int height) {
    if (!ptr || !(*ptr) || height < 1 || width < 1) return -1;

    int sum = 0;
    for (int i = 0; i < height; sum += sum_row(*(ptr+i), width), ++i);
    return sum;
}

int sum_row(int *ptr, int width){
    if(!ptr || width < 1) return -1;

    int sum = 0;
    for (int i = 0; i < width; sum += *(ptr + i), ++i);
    return sum;
}
