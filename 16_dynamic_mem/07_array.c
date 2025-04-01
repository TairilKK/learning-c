#include <stdlib.h>
#include <stdio.h>
#include "07_array.h"

/* 0406 START 0406 */

int array_create(struct array_t *a, int N){
    if(a==NULL||N<1)
        return 1;
    a->ptr = (int *) malloc(sizeof(int)*N);
    if(a->ptr==NULL)
        return 2;
    a->size = 0;
    a->capacity = N;

    return 0;
}
int array_push_back(struct array_t *a, int value){
    if(a==NULL||a->ptr==NULL)
        return 1;
    if(a->size>=0 && a->capacity>0 && a->size == a->capacity)
        return 2;
    if(a->size >= a->capacity)
        return 1;
    if(a->size<0)
        return 1;
    if(a->capacity<1)
        return 1;
    if(a->size>a->capacity)
        return 1;

    *(a->ptr+a->size)=value;
    a->size++;
    return 0;
}
void array_display(const struct array_t *a){
    if(a==NULL||a->ptr==NULL||a->size<1||a->capacity<1||a->size>a->capacity)
        return;
    for(int i=0;i<a->size&&i<a->capacity;i++)
        printf("%d ",*(a->ptr+i));
}
void array_destroy(struct array_t *a){
    if(a==NULL||a->ptr==NULL)
        return;
    free(a->ptr);
}


/* 0406  END  0406 */



/* 4007 START 4007 */

int array_copy(const struct array_t *src, struct array_t *dest){
    if(!src || !src->ptr || !dest || src->capacity < 1 || src->size < 0 || src == dest) return 1;
    if (array_create(dest, src->capacity)!= 0) return 2;
    for(int i = 0; i< src->size; ++i)
        *(dest->ptr + i) = *(src->ptr + i);

    dest->size = src->size;
    dest->capacity = src->capacity;
    return 0;
}

int array_separate(const struct array_t *a, struct array_t *odd, struct array_t *even){
    if(!a || !a->ptr || !odd || !even || a->size<0 || a->capacity < 1 || a->size > a->capacity || a == odd || a == even || odd == even) return -1;

    int odd_counter = 0;
    for(int i = 0; i<a->size; ++i)
        if(*(a->ptr+i)%2 == 1 || *(a->ptr+i)%2 == -1) odd_counter++;

    if(odd_counter == a->size) {
        if(array_copy(a, odd) != 0)
            return 0;
        return 1;
    }

    if(odd_counter == 0) {
        if(array_copy(a, even) != 0){
            array_destroy(odd);
            return 0;
        }
        return 2;
    }

    if(array_create(odd, odd_counter) != 0)
        return 0;
    if(array_create(even, a->size - odd_counter) != 0) {
        array_destroy(odd);
        return 0;
    }

    for(int i = 0; i<a->size; ++i) {
        if (*(a->ptr + i) % 2 == 1 || *(a->ptr+i)%2 == -1)
            *(odd->ptr + odd->size++) = *(a->ptr + i);
        else
            *(even->ptr + even->size++) = *(a->ptr + i);
    }

    return 3;
}
/* 4007  END  4007 */
