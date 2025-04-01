//
// Created by jdobr on 22.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "05_matrix_utils.h"


struct matrix_t* matrix_create_struct(int width, int height){
    if(width < 1 || height < 1) return NULL;

    struct matrix_t * m = (struct matrix_t *) calloc(1, sizeof (struct matrix_t));
    if(!m) return NULL;

    if(matrix_create(m, width, height) != 0){
        free(m);
        return NULL;
    }
    return m;
}

int matrix_create(struct matrix_t *m, int width, int height){
    if(!m || width < 1 || height < 1) return 1;

    m->width = width;
    m->height = height;
    m->ptr = (int **)calloc(height, sizeof(int *));
    if(!m->ptr) { matrix_destroy(m); return 2; }

    m->width = width;
    m->height = 0;
    for(int i = 0; i < height; ++i){
        *( m->ptr + i ) = (int *)calloc(width, sizeof(int));
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
        free(*(m->ptr + i));
    free(m->ptr);
}
void matrix_destroy_struct(struct matrix_t **m){
    if(!m) return;
    matrix_destroy(*m);
    free(*m);
    *m = NULL;
}


int matrix_save_b(const struct matrix_t *m, const char *filename){
    if(!m || !m->ptr || m->width < 1 || m->height < 1 || filename == NULL) return 1;

    FILE * f = fopen(filename, "wb");
    if(!f) return 2;

    fwrite(&m->width,sizeof(int),1, f);
    fwrite(&m->height,sizeof(int),1, f);
    for(int h = 0; h < m->height; ++h)
        for(int w = 0; w < m->width; fwrite((*(m->ptr + h) + w),sizeof(int),1, f), w++);

    fclose(f);
    return 0;
}


int matrix_save_t(const struct matrix_t *m, const char *filename){
    if(!m || !m->ptr || m->width < 1 || m->height < 1 || filename == NULL) return 1;

    FILE * f = fopen(filename, "w");
    if(!f) return 2;

    fprintf(f,"%d %d\n",m->width, m->height);
    for(int h = 0; h < m->height; fprintf(f,"\n"), ++h)
        for(int w = 0; w < m->width; fprintf(f,"%d ", *(*(m->ptr + h) + w)) , w++);

    fclose(f);
    return 0;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m){
    if(!m || !m->ptr || m->width < 1 || m->height < 1)
        return NULL;

    struct matrix_t * m_t = matrix_create_struct(m->height, m->width);
    if(!m_t) return NULL;

    for(int h = 0; h < m->height; ++h)
        for(int w = 0; w < m->width; *(*(m_t->ptr + w) + h) = *(*(m->ptr + h) + w), w++);

    return m_t;
}
