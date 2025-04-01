//
// Created by jdobr on 31.08.2023.
//
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "04_functions.h"

char* lower_to_upper(const char *in){
    if(!in) return NULL;

    int size = (int)strlen(in);
    char * res = calloc(size + 1, sizeof(char));
    if(!res)
        return NULL;
    for(int i = 0; i < size; ++i)
       (*(in + i) <= 'z' && *(in + i) >= 'a') ? (*(res + i) = *(in + i) - 'a' + 'A') : (*(res + i) = *(in + i));

    return res;
}

char* upper_to_lower(const char *in) {
    if(!in) return NULL;
    int size = (int)strlen(in);
    char * res = calloc(size + 1, sizeof(char));
    if(!res)
        return NULL;
    for(int i = 0; i < size; ++i)
        (*(in + i) <= 'Z' && *(in + i) >= 'A') ? (*(res + i) = *(in + i) - 'A' + 'a') : (*(res + i) = *(in + i));

    return res;
}

char* space_to_dash(const char *in){
    if(!in) return NULL;
    int size = (int)strlen(in);
    char * res = calloc(size + 1, sizeof(char));
    if(!res)
        return NULL;
    for(int i = 0; i < size; ++i)
        (*(in + i) == ' ') ? (*(res + i) = '_') : (*(res + i) = *(in + i));

    return res;
}

char* reverse_letter(const char *in){
    if(!in) return NULL;
    int size = (int)strlen(in);
    char * res = calloc(size + 1, sizeof(char));
    if(!res)
        return NULL;
    for(int i = 0; i < size; ++i)
        (*(in + i) <= 'Z' && *(in + i) >= 'A') ? (*(res + i) = 'Z' - (*(in + i) - 'A')) : ((*(in + i) <= 'z' && *(in + i) >= 'a') ? (*(res + i) = 'z' - (*(in + i) - 'a')) : (*(res + i) = *(in + i)));

    return res;
}

void free_texts(char ** t){
    if(!t) return;
    for(int i = 0; *(t + i); ++i)
        free(*(t+i));
    free(t);
}

char ** text_modifier(const char *text, int n, ...){
    if(!text || n < 1) return NULL;

    char ** t = calloc(n + 1, sizeof (char *));
    if(!t) return NULL;

    va_list v;
    va_start(v, n);
    char * (*func)(const char *) = NULL;
    for(int i = 0; i < n; ++i){
        func = va_arg(v, char * (*) (const char *));
        *(t + i) = func(text);
        if(!*(t + i)){
            for(int j = 0; j < i; ++j)
                free(*(t + j));
            free(t);
            va_end(v);
            return NULL;
        }
    }
    va_end(v);
    *(t+n) = NULL;
    return t;
}
