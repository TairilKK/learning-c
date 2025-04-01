#include <stdio.h>
#include <stdlib.h>

#include "08_cross.h"

#define WORD_CAPACITY 11

int main() {
    char ** result = NULL;
    char ** first = NULL;
    char ** second = NULL;

    char * w1 = (char *)calloc(WORD_CAPACITY, sizeof (char));
    if(!w1){
        printf("Failed to allocate memory");
        return 8;
    }

    char * w2 = (char *)calloc(WORD_CAPACITY, sizeof (char));
    if(!w2){
        printf("Failed to allocate memory");
        free(w1);
        return 8;
    }

    char * w3 = (char *)calloc(WORD_CAPACITY, sizeof (char));
    if(!w3){
        printf("Failed to allocate memory");
        free(w1);
        free(w2);
        return 8;
    }

    char * w4 = (char *)calloc(WORD_CAPACITY, sizeof (char));
    if(!w4){
        printf("Failed to allocate memory");
        free(w1);
        free(w2);
        free(w3);
        return 8;
    }
    char c = 0;
    printf("Enter words: ");
    for(int j = 0; j < (WORD_CAPACITY - 1) && (c = getchar()) != ' ' && c != '\n';  ++j){
        if(c >= 'A' && c <= 'Z')
            *(w1 + j) = c;
        else{
            printf("Incorrect input");
            free(w1);
            free(w2);
            free(w3);
            free(w4);
            return 1;
        }
    }
    if(c != ' ' && c != '\n')
        while((c = (char) getchar())!= ' ' || c != '\n');
    if(c == '\n' || validation(w1) != 1){
        printf("Incorrect input");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 1;
    }

    for(int j = 0; j < (WORD_CAPACITY - 1) && (c = getchar()) != ' ' && c != '\n';  ++j){
        if(c >= 'A' && c <= 'Z')
            *(w2 + j) = c;
        else{
            printf("Incorrect input");
            free(w1);
            free(w2);
            free(w3);
            free(w4);
            return 1;
        }
    }
    if(c != ' ' && c != '\n')
        while((c = (char) getchar())!= ' ' || c != '\n');
    if(c == '\n' || validation(w2) != 1){
        printf("Incorrect input");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 1;
    }

    for(int j = 0; j < (WORD_CAPACITY - 1) && (c = getchar()) != ' ' && c != '\n';  ++j){
        if(c >= 'A' && c <= 'Z')
            *(w3 + j) = c;
        else{
            printf("Incorrect input");
            free(w1);
            free(w2);
            free(w3);
            free(w4);
            return 1;
        }
    }
    if(c != ' ' && c != '\n')
        while((c = (char) getchar())!= ' ' || c != '\n');
    if(c == '\n' || validation(w3) != 1){
        printf("Incorrect input");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 1;
    }

    for(int j = 0; j < (WORD_CAPACITY - 1) && (c = getchar()) != ' ' && c != '\n';  ++j){
        if(c >= 'A' && c <= 'Z')
            *(w4 + j) = c;
        else{
            printf("Incorrect input");
            free(w1);
            free(w2);
            free(w3);
            free(w4);
            return 1;
        }
    }
    if(c != '\n' )
        while((c = (char) getchar()) != '\n');
    if(c == ' ' || validation(w4) != 1){
        printf("Incorrect input");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 1;
    }

    int res = create_double_leading_word_cross(w1, w2, w3, w4, &result, &first, &second);
    if(res == 2){
        printf("Unable to make two crosses");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 0;
    }
    else if(res == 3){
        printf("Failed to allocate memory");
        free(w1);
        free(w2);
        free(w3);
        free(w4);
        return 8;
    }

    display(first);
    printf("\n");

    display(second);
    printf("\n");

    display(result);

    destroy(first);
    destroy(second);
    destroy(result);

    free(w1);
    free(w2);
    free(w3);
    free(w4);
    return 0;
}
