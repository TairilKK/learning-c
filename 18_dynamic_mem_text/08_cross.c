//
// Created by jdobr on 29.08.2023.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "08_cross.h"

int max_int(int a, int b){
    return a >= b ? a : b;
}

void destroy(char **w){
    if(!w || !*w) return;
    for(int i = 0; *(w + i); ++i)
        free(*(w+i));
    free(w);
}

void display(char ** w){
    if(!w || !*w) return;

    for(int i = 0; *(w + i); printf("\n"), ++i)
        for(int j = 0; *(*(w + i) + j) != '\0'; printf("%c",*(*(w + i) + j)), ++j);
}

int validation(char * w){
    if(!w) return -1;
    while(*w != '\0'){
        if(*w < 'A' || *w > 'Z')
            return 0;
        w++;
    }
    return 1;
}

int firstLetterCross(const char *first, const char *second, int * w, int * h){
    if(validation((char *)first) != 1 || validation((char *)second) != 1 || !w || !h) return -1;

    int res = 0;
    while(*second != '\0'){
        for(int i = 0; i < (int) strlen(first); ++i)
            if(*second == *(first + i)) {
                *h = i;
                *w = res;
                return 0;
            }
        res++;
        second++;
    }

    return -2;
}
int create_leading_word_cross(const char *first, const char *second, char ***result){
    if(validation((char *)first) != 1 || validation((char *)second) != 1 || !result) return -1;

    /* Przeszukiwanie */
    int w = 0, h = 0;
    int res = firstLetterCross((char *) first, (char *) second, &w, &h);
    if(res == -2) {
        *result = NULL;
        return -2;
    }

    /* Alokacja pamięci */
    int size = (int) strlen(first);
    (*result) = (char **) calloc(size + 1, sizeof(char *));
    if(!(*result)) {
        *result = NULL;
        return -3;
    }

    for(int i = 0; i < size; ++i) {
        if (i != h) {
            *((*result) + i) = (char *) calloc(2 + w, sizeof(char));
            if (!(*((*result) + i))) {
                while(i > 0) {
                    --i;
                    free(*((*result) + i));
                }
                free(*result);
                *result = NULL;
                return -3;
            }
        } else {
            *((*result) + i) = (char *) calloc((int) strlen(second) + 1, sizeof(char));
            if (!(*((*result) + i))) {
                while(i > 0) {
                    --i;
                    free(*((*result) + i));
                }
                free(*result);
                *result = NULL;
                return -3;
            }
        }
    }
    *((*result) + size) = NULL;

    for(int j = 0; j < size; ++j)
        for(int x = 0; x < w; ++x)
            *(*((*result) + j) + x) = ' ';

    for(int j = 0; j < size; ++j)
        *(*((*result) + j) + w) = *(first + j);

    for(int x = 0; x < (int)strlen(second); ++x)
        *(*((*result) + h) + x) = *(second + x);

    return h;
}

int create_double_leading_word_cross(
        const char *first, const char *second, const char *third, const char *fourth,
        char ***result, char ***first_cross, char ***second_cross){

    if(validation((char *)first) != 1 || validation((char *)second) != 1 || validation((char *)third) != 1 || validation((char *)fourth) != 1
       || !result || !first_cross || !second_cross) return 1;

    int firstCrossHeight = create_leading_word_cross(second, first, first_cross);
    if(firstCrossHeight == -2) {
        *first_cross = NULL;
        *second_cross = NULL;
        *result = NULL;
        return 2;
    }
    else if(firstCrossHeight == -3) {
        destroy(*first_cross);
        *first_cross = NULL;
        *second_cross = NULL;
        *result = NULL;
        return 3;
    }

    int secondCrossHeight = create_leading_word_cross(fourth, third, second_cross);
    if(secondCrossHeight == -2) {
        destroy(*first_cross);
        *first_cross = NULL;
        *second_cross = NULL;
        *result = NULL;
        return 2;
    }
    else if(secondCrossHeight == -3) {
        destroy(*first_cross);
        *first_cross = NULL;
        *second_cross = NULL;
        *result = NULL;
        return 3;
    }

    int f_height = 0;
    for(int i = 0; *((*first_cross) + i); ++f_height, ++i);
    int s_height = 0;
    for(int i = 0; *((*second_cross) + i); ++s_height, ++i);
    int r_size = max_int(firstCrossHeight, secondCrossHeight) + max_int(f_height - firstCrossHeight, s_height - secondCrossHeight);


    *result = (char **)calloc(r_size + 1, sizeof(char *));
    if(!(*result)){
        destroy(*first_cross);
        destroy(*second_cross);
        *first_cross = NULL;
        *second_cross = NULL;
        *result = NULL;
        return 3;
    }
    *((*result) + r_size) = NULL;

    int max_h = max_int(secondCrossHeight, firstCrossHeight);
    int max_f_width = (int)strlen(first);
    int act_w_f;
    int act_w_s;
    secondCrossHeight -= max_h;
    firstCrossHeight -= max_h;
    int c_secondCrossHeight = secondCrossHeight;
    int c_firstCrossHeight = firstCrossHeight;

    for(int i = 0; i < r_size; ++i){
        act_w_f = 0;
        act_w_s = 0;
        if(secondCrossHeight >= 0 && secondCrossHeight < s_height) {
            for (int j = 0; *(*(*(second_cross) + secondCrossHeight) + j) != '\0'; act_w_s++, j++);
            act_w_f = max_f_width + 3; // + 3 ' '
        }
        else if(firstCrossHeight >= 0 && firstCrossHeight < f_height) {
            for (int j = 0; *(*(*(first_cross) + firstCrossHeight) + j) != '\0'; act_w_f++, j++);
        }
        else
            break;

        *((*result) + i) = (char *) calloc(act_w_f + act_w_s + 1, sizeof (char));
        if (!(*((*result) + i))) {
            while (i > 0) {
                i--;
                free(*((*result) + i));
            }
            free(*result);
            destroy(*first_cross);
            destroy(*second_cross);
            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;
            return 3;
        }
        firstCrossHeight++;
        secondCrossHeight++;
    }

    /* Przypisywanie DANYCH */
    for(int i = 0; (*((*result) + i)); ++i) {
        act_w_f = 0;
        act_w_s = 0;
        if (c_secondCrossHeight >= 0 && c_secondCrossHeight < s_height) {
            for (int j = 0; *(*(*(second_cross) + c_secondCrossHeight) + j) != '\0'; act_w_s++, j++);
            act_w_f = max_f_width + 3;
        } else if (c_firstCrossHeight >= 0 && c_firstCrossHeight < f_height)
            for (int j = 0; *(*(*(first_cross) + c_firstCrossHeight) + j) != '\0'; act_w_f++, j++);
        else
            break;

        for(int j = 0; j < act_w_f + act_w_s; *(*((*result) + i) + j) = ' ', ++j);

        if(c_firstCrossHeight >= 0 && c_firstCrossHeight < f_height) {
            strcpy(*(*(result) + i), *(*(first_cross) + c_firstCrossHeight));
            if(c_secondCrossHeight >= 0 && c_secondCrossHeight < s_height)
                *(*(*(result) + i) + (int)strlen(*(*(first_cross) + c_firstCrossHeight))) = ' ';
        }
        if(c_secondCrossHeight >= 0 && c_secondCrossHeight < s_height)
            strcpy(*(*(result) + i) + max_f_width + 3, *(*(second_cross) + c_secondCrossHeight));

        c_firstCrossHeight++;
        c_secondCrossHeight++;
    }
    return 0;
}
