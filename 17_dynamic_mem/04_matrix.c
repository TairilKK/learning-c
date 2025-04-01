//
// Created by jdobr on 22.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "04_matrix.h"


int matrix_create(struct matrix_t *m, int width, int height){
    if(!m || width < 1 || height < 1) return 1;

    m->width = width;
    m->height = height;
    m->ptr = (int **)calloc(height, sizeof(int *));
    if(!m->ptr) { matrix_destroy(m); return 2; }

    m->width = width;
    m->height = 0;
    for(int i = 0; i < height; ++i){
        *(m->ptr+ i ) = (int *)calloc(width, sizeof(int));
        if(!*(m->ptr + i)){
            matrix_destroy(m);
            return 2;
        }
        m->height++;
    }
    m->height = height;

    return 0;
}

int matrix_read(struct matrix_t *m){
    if(!m || !m->ptr || m->width < 1 || m->height < 1) return 1;
    printf("Podaj wartości: ");
    for(int h = 0; h < m->height; ++h)
        for(int w = 0; w < m->width; w++)
            if(scanf(" %d",(*(m->ptr + h) + w)) != 1)
                return 2;

    return 0;
}

void matrix_display(const struct matrix_t *m){
    if(!m || !m->ptr || m->width < 1 || m->height < 1) return;

    for(int h = 0; h < m->height; printf("\n"), ++h)
        for(int w = 0; w < m->width; printf("%d ", *(*(m->ptr + h) + w)) , w++);
}

void matrix_destroy(struct matrix_t *m){
    if(!m || !(m->ptr)) return;
    for(int i = 0; i < m->height; i++)
        if(*(m->ptr + i))free(*(m->ptr + i));
    free(m->ptr);
}
