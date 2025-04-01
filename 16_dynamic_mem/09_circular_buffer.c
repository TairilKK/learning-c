//
// Created by jdobr on 22.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "09_circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if(!a || N < 1) return 1;
    a->ptr =(int *) calloc(N, sizeof(int));
    if(!a->ptr) return 2;
    a->capacity = N;
    a->begin = 0;
    a->end = 0;
    a->full = 0;
    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if(!cb || N < 2) return 1;
    *cb = (struct circular_buffer_t *) calloc(1, sizeof(struct circular_buffer_t));
    if(!(*cb)) return 2;
    if(circular_buffer_create(*cb, N) != 0){ circular_buffer_destroy_struct(cb); return 2;}
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a){
    if(!a) return;
    free(a->ptr);
}
void circular_buffer_destroy_struct(struct circular_buffer_t **a){
    if(!a) return;
    circular_buffer_destroy(*a);
    free(*a);
}


int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if(!cb || !cb->ptr || cb->capacity<1 || cb->begin < 0 || cb->end < 0 || cb->begin >= cb->capacity || cb->end >= cb->capacity) return 1;

    if(cb->full)
        cb->begin = (cb->begin + 1) % cb->capacity;

    *(cb->ptr + cb->end) = value;
    cb->end = (cb->end + 1) % cb->capacity;

    if(cb->end == cb->begin)
        cb->full = 1;

    return 0;
}


int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if(!a || !a->ptr || a->begin < 0 || a->end < 0 || a->capacity < 1 || a->end >= a->capacity || a->begin >= a->capacity)
    {
        ERROR(1);
        return 0;
    }
    if(circular_buffer_empty(a)){ ERROR(2); return 1;}

    int res = *(a->ptr + a->begin);
    a->begin++;
    if(a->begin == a->capacity) a->begin -= a->capacity;
    a->full = 0;
    ERROR(0);
    return res;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
    if(!a || !a->ptr || a->begin < 0 || a->end < 0 || a->capacity < 1 || a->end >= a->capacity || a->begin >= a->capacity)
    {
        ERROR(1);
        return 0;
    }
    if(circular_buffer_empty(a)){ ERROR(2); return 1;}

    a->end--;
    if(a->end < 0) a->end += a->capacity;
    int res = *(a->ptr + a->end);

    a->full = 0;

    ERROR(0);
    return res;
}

int circular_buffer_empty(const struct circular_buffer_t *cb){

    if(!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->capacity < 1 || cb->end >= cb->capacity || cb->begin >= cb->capacity) return -1;
    return (cb->begin == cb->end && !cb->full) ? 1 : 0;
}
int circular_buffer_full(const struct circular_buffer_t *cb){
    if(!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->capacity < 1 || cb->end >= cb->capacity || cb->begin >= cb->capacity) return -1;
    return (cb->full == 1) ? 1 : 0;
}

void circular_buffer_display(const struct circular_buffer_t *cb) {
    if(!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->capacity < 1 || cb->end >= cb->capacity || cb->begin >= cb->capacity ||
            circular_buffer_empty(cb)) return;

    int i = cb->begin;
    int j = 0;

    while (j < cb->capacity) {
        printf("%d ", *(cb->ptr + i));
        i = (i + 1) % cb->capacity;
        j++;
        if (i == cb->end && !cb->full) break;
    }
}
