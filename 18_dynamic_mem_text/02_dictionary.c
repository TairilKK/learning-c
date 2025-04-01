//
// Created by jdobr on 27.08.2023.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

struct dictionary_t* create_dictionary(int N, int *err_code){
    if(N<1){ ERROR(1); return NULL; }

    struct dictionary_t * d = calloc(1, sizeof(struct dictionary_t));
    if(!d){ ERROR(2); return NULL; }
    d->size = 0;
    d->capacity = N;
    d->wc = calloc(N, sizeof(struct word_count_t));
    if(!(d->wc)){ ERROR(2); free(d); return NULL; }
    for(int i = 0; i < N; ++i) {
        (d->wc + i)->counter = 0;
        (d->wc + i)->word = NULL;
    }
    ERROR(0);
    return d;
}

void destroy_dictionary(struct dictionary_t** d){
    if( !d || !(*d) || (*d)->capacity < 1 || (*d)->size < 0 || (*d)->capacity < (*d)->size ) return;
    for(int i = 0; i < (*d)->size; ++i)
        free(((*d)->wc + i)->word);
    free((*d)->wc);
    free(*d);
    *d = NULL;
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size || !word) return NULL;
    for(int i = 0; i < d->size; ++i)
        if(!strcmp((d->wc + i)->word, word))
            return (d->wc + i);
    return NULL;
}

void dictionary_display(const struct dictionary_t *d){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size) return;
    for(int i = 0; i < d->size; printf("%s %d\n", (d->wc + i)->word, (d->wc + i)->counter), ++i);
}

int dictionary_add_word(struct dictionary_t *d, const char *word){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size || !word) return 1;

    struct word_count_t * wword = dictionary_find_word(d, word);
    if(wword) {
        wword->counter++;
        return 0;
    }

    if(d->size == d->capacity){
        struct word_count_t * temp = realloc(d->wc, 2 * d->capacity * sizeof(struct word_count_t));
        if(!temp) return 2;
        d->wc = temp;
        d->capacity *= 2;
    }

    (d->wc + d->size)->word = calloc(strlen(word) + 1, sizeof(char));
    if(!((d->wc + d->size)->word)) return 2;
    strcpy((d->wc + d->size)->word, word);
    (d->wc + d->size)->counter = 1;
    d->size++;

    return 0;
}