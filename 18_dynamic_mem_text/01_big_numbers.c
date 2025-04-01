//
// Created by jdobr on 30.08.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "big_numbers.h"

int create(struct big_numbers_t *bn, int capacity){
    if(!bn || capacity < 1) return 1;
    bn->size = 0;
    bn->capacity = capacity;
    bn->big_number = (char **) calloc(capacity, sizeof (char *));
    if(!bn->big_number) { bn = NULL; return 2; }
    return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity){
    if(!bn || capacity < 1) return 1;
    *bn = (struct big_numbers_t *)calloc(1, sizeof (struct big_numbers_t));
    if(!(*bn))return 2;
    if(create(*bn, capacity) == 2){ free(*bn); *bn = NULL; return 2; }
    return 0;
}

void destroy(struct big_numbers_t *bn){
    if(!bn || !bn->big_number || bn->size < 0 || bn->capacity < 1 || bn->size > bn->capacity) return;

    for (int i = 0; i < bn->size; ++i)
        if(*(bn->big_number + i))free(*(bn->big_number + i));
    free(bn->big_number);

}

void destroy_big_numbers(struct big_numbers_t **bn){
    if(!bn || !(*bn) || !(*bn)->big_number || (*bn)->size < 0 || (*bn)->capacity < 1 || (*bn)->size > (*bn)->capacity) return;
    destroy(*bn);
    free(*bn);
}

void display(const struct big_numbers_t *bn){
    if(!bn || !bn->big_number || bn->size < 0 || bn->capacity < 1 || bn->size > bn->capacity) return;
    for(int i = 0; i < bn->size; printf("%s\n",*(bn->big_number + i)), ++i);
}

int isNumber(char * a){
    if(!a) return -1;
    if(*a == '\0')
        return 0;
    if(*a == '0' && strlen(a) > 1)
        return 0;
    if(*a == '-' && strlen(a) > 1)
        a++;
    else if(*a == '-')
        return 0;

    while(*a != '\0'){
        if(*a < '0' || *a > '9')
            return 0;
        a++;
    }
    return 1;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number){
    if(!big_number || !bn || !bn->big_number || bn->size < 0 || bn->capacity < 1 || bn->size > bn->capacity || isNumber((char *)big_number) != 1) return 1;

    if(bn->size == bn->capacity)
        return 3;

    int size = (int)strlen(big_number);
    char * copy = calloc(size + 1, sizeof(char));
    if(!copy)
        return 2;

    strcpy(copy, big_number);

    *(bn->big_number + bn->size) = copy;
    bn->size++;
    return 0;
}