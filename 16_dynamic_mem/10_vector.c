#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

int vector_create_struct(struct vector_t **a, int N){
    if(a==NULL || N<1)
        return 1;

    *a = (struct vector_t *) calloc (1, sizeof(struct vector_t));

    if(*a == NULL)
        return 2;
    int res = vector_create(*a, N);

    if (res == 2){
        free(*a);
        return 2;
    }
    return 0;
}
void vector_destroy_struct(struct vector_t **a){
    if(a == NULL || *a == NULL)
        return;
    vector_destroy(*a);
    free(*a);
}

int vector_create(struct vector_t *a, int N){
    if(a==NULL || N<1)
        return 1;
    a->ptr = (int *)calloc(N, sizeof(int));
    if(a->ptr == NULL)
        return 2;
    a->capacity = N;
    a->size = 0;
    return 0;
}

void vector_destroy(struct vector_t *a){
    if(a!=NULL)
        free(a->ptr);
}

void vector_display(const struct vector_t *a){
    if(a==NULL || a->ptr==NULL|| a->size>a->capacity)
        return;
    for(int i=0;i<a->size;++i)
        printf("%d ",*((a->ptr)+i));
}

int vector_push_back(struct vector_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->capacity<1 || a->size<0 || a->size > a->capacity)
        return 1;

    if( a->size == a->capacity ){
        int *temp = realloc(a->ptr, 2 * a->capacity * sizeof(int));
        if(temp == NULL)
            return 2;
        a->ptr = temp;
        a->capacity *= 2;
    }
    *((a->ptr) + a->size) = value;
    a->size++;
    return 0;
}
int vector_erase(struct vector_t *a, int value){
    if(a==NULL || a->ptr==NULL || a->capacity<1||a->size<0 || a->size>a->capacity)
        return -1;
    int how = 0, i = 0;

    while(i < a->size){
        if(*(a->ptr + i) == value) {
            how++;
            a->size--;
            for (int j = i; j < a->size; ++j)
                *(a->ptr + j) = *(a->ptr + j + 1);
            --i;
        }
        ++i;
    }

    if(a->size < (0.25 * a->capacity)){
        a->capacity /= 2;
        if(a->capacity == 0)
            a->capacity++;
        int * temp = (int *) realloc(a->ptr, a->capacity * sizeof (int));
        if(temp != NULL)
            a->ptr = temp;
    }


    return how;
}

