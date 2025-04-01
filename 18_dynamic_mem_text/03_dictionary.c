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
    if((*d)->wc) {
        for (int i = 0; i < (*d)->size; ++i)
            free(((*d)->wc + i)->word);
        free((*d)->wc);
    }
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

/* zadanie 08 */

int dictionary_sort_alphabetically(struct dictionary_t *d){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size) return 1;

    char * tchar;
    int tint;
    for(int i = 0; i < d->size - 1; ++i)
        for(int j = 0; j < d->size - 1 - i; ++j){
            if(strcmp((d->wc + j)->word, (d->wc + j + 1)->word) > 0){
                tchar = (d->wc + j)->word;
                tint = (d->wc + j)->counter;

                (d->wc + j)->word = (d->wc + j + 1)->word;
                (d->wc + j)->counter = (d->wc + j + 1)->counter;

                (d->wc + j + 1)->word = tchar;
                (d->wc + j + 1)->counter = tint;
            }
        }
    for(int i = 0; i < d->size - 1; ++i)
        for(int j = 0; j < d->size - 1 - i; ++j){
            if(*((d->wc + j)->word) >= 'a' && *((d->wc + j)->word) <= 'z' && *((d->wc + j + 1)->word) >= 'A' && *((d->wc + j + 1)->word) <= 'Z'){
                tchar = (d->wc + j)->word;
                tint = (d->wc + j)->counter;

                (d->wc + j)->word = (d->wc + j + 1)->word;
                (d->wc + j)->counter = (d->wc + j + 1)->counter;

                (d->wc + j + 1)->word = tchar;
                (d->wc + j + 1)->counter = tint;
            }
        }

    return 0;
}
int dictionary_sort_occurence(struct dictionary_t *d){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size) return 1;

    char * tchar;
    int tint;
    dictionary_sort_alphabetically(d);
    for(int i = 0; i < d->size - 1; ++i)
        for(int j = 0; j < d->size - 1 - i; ++j){
            if((d->wc + j)->counter < (d->wc + j + 1)->counter){
                tchar = (d->wc + j)->word;
                tint = (d->wc + j)->counter;

                (d->wc + j)->word = (d->wc + j + 1)->word;
                (d->wc + j)->counter = (d->wc + j + 1)->counter;

                (d->wc + j + 1)->word = tchar;
                (d->wc + j + 1)->counter = tint;
            }
        }

    return 0;
}

int save_dictionary_b(const struct dictionary_t *d, const char *filename){
    if(!d || !d->wc || d->capacity < 1 || d->size < 0 || d->capacity < d->size || !filename) return 1;

    FILE *f = fopen(filename, "wb");
    if(!f) return 2;

    fwrite(&(d->size), sizeof (int), 1, f);

    int len = 0;
    for(int i = 0; i < d->size; ++i){
        len = (int)strlen((d->wc + i)->word);
        fwrite(&len, sizeof(int), 1, f);
        fwrite((d->wc + i)->word, sizeof(char), len, f);
        fwrite(&((d->wc + i)->counter), sizeof(int), 1, f);
    }
    fclose(f);
    return 0;
}
struct dictionary_t* load_dictionary_b(const char *filename, int *err_code){
    if(!filename){ ERROR(1); return NULL; }

    FILE *f = fopen(filename, "rb");
    if(!f) { ERROR(2); return NULL; }

    if(feof(f)){ fclose(f); ERROR(3); return NULL; }

    int size = 0;
    fread(&size, sizeof (int), 1, f);
    if(size < 1){ fclose(f); ERROR(3); return NULL; }

    struct dictionary_t * d = create_dictionary(size, NULL);
    if(!d) { fclose(f); ERROR(4); return NULL; }
    d->size = size;
    int len;
    for(int i = 0; i < d->size; ++i){
        if((int)fread(&len, sizeof(int), 1, f) != 1) { fclose(f); destroy_dictionary(&d); ERROR(3); return NULL; }
        if(len < 1) { fclose(f); destroy_dictionary(&d); ERROR(3); return NULL; }

        (d->wc + i)->word = calloc(len + 1, sizeof(char));
        if(!((d->wc + i)->word)){ fclose(f); destroy_dictionary(&d); ERROR(4); return NULL; }

        if((int)fread((d->wc + i)->word, sizeof(char), len, f) != len) { fclose(f); destroy_dictionary(&d); ERROR(3); return NULL; }
        if((int)fread(&((d->wc + i)->counter), sizeof(int), 1, f) != 1) { fclose(f); destroy_dictionary(&d); ERROR(3); return NULL; }
    }
    ERROR(0);
    fclose(f);
    return d;
}
