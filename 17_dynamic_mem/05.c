#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_utils.h"


int main() {
    matrix_display(NULL);
    struct matrix_t * m;
    struct matrix_t * m_t;
    int w, h;

    printf("Podaj szerokość i wysokość: ");
    if(scanf(" %d %d", &w, &h) != 2){
        printf("incorrect input");
        return 1;
    }

    if(w < 1 || h < 1){
        printf("incorrect input data");
        return 2;
    }

    if((m = matrix_create_struct(w, h)) == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    if(matrix_read(m) == 2){
        printf("incorrect input");
        matrix_destroy_struct(&m);
        return 1;
    }
    while(getchar() != '\n');

    char * input = calloc(40, sizeof(char));
    if(!input){
        printf("Failed to allocate memory");
        matrix_destroy_struct(&m);
        return 8;
    }
    printf("Podaj sciezke do pliku:\n");
    scanf("%39[^\n]", input);
    while(getchar() != '\n');


    if(strlen(input) <= 4){
        printf("Unsupported file format");
        matrix_destroy_struct(&m);
        free(input);
        return 7;
    }
    if(strcmp(input + strlen(input)- 4, ".bin") == 0){
        m_t = matrix_transpose(m);
        if(!m_t){
            printf("Failed to allocate memory");
            matrix_destroy_struct(&m);
            free(input);
            return 8;
        }
        if(matrix_save_b(m_t, input) != 0){
            printf("Couldn't create file");
            matrix_destroy_struct(&m);
            matrix_destroy_struct(&m_t);
            free(input);
            return 5;
        }
    }
    else if(strcmp(input + strlen(input)- 4, ".txt") == 0){
        m_t = matrix_transpose(m);
        if(!m_t){
            printf("Failed to allocate memory");
            matrix_destroy_struct(&m);
            free(input);
            return 8;
        }
        if(matrix_save_t(m_t, input) != 0){
            printf("Couldn't create file");
            matrix_destroy_struct(&m);
            matrix_destroy_struct(&m_t);
            free(input);
            return 5;
        }
    }
    else{
        printf("Unsupported file format");
        matrix_destroy_struct(&m);
        free(input);
        return 7;
    }

    printf("File saved");
    matrix_destroy_struct(&m);
    matrix_destroy_struct(&m_t);
    free(input);

    return 0;
}
