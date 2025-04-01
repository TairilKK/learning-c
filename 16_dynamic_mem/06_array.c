#include <stdlib.h>
#include <stdio.h>
#include "06_array.h"


int array_create(struct array_t *a, int N){
    if(a==NULL||N<1)
        return 1;
    a->ptr= (int *) malloc(sizeof(int)*N);
    if(a->ptr==NULL)
        return 2;
    a->size=0;
    a->capacity=N;

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
