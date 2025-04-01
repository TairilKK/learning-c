#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "06_matrix_utils.h"

int main() {
    matrix_copy(NULL);
    matrix_read(NULL);
    matrix_save_b(NULL, NULL);
    matrix_save_t(NULL, NULL);

    struct matrix_t * m1;
    struct matrix_t * m2;
    char * filename = calloc(20, sizeof (char));
    int error = 0;

    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }

    /* Pierwszy plik */

    printf("Podaj nazwę pierwszego pliku: ");
    scanf("%19[^\n]", filename);
    while (getchar() != '\n');

    if(strlen(filename) <= 4){
        printf("Unsupported file format");
        free(filename);
        return 7;
    }
    if(strcmp(filename + strlen(filename)- 4, ".bin") == 0){
        m1 = matrix_load_b(filename, &error);
        if(error == 2){
            printf("Couldn't open file");
            matrix_destroy_struct(&m1);
            free(filename);
            return 4;
        }
        else if(error == 3){
            printf("File corrupted");
            matrix_destroy_struct(&m1);
            free(filename);
            return 6;
        }
        else if(error == 4){
            printf("Failed to allocate memory");
            free(filename);
            return 8;
        }
    }
    else if(strcmp(filename + strlen(filename)- 4, ".txt") == 0){
        m1 = matrix_load_t(filename, &error);
        if(error == 2){
            printf("Couldn't open file");
            matrix_destroy_struct(&m1);
            free(filename);
            return 4;
        }
        else if(error == 3){
            printf("File corrupted");
            matrix_destroy_struct(&m1);
            free(filename);
            return 6;
        }
        else if(error == 4){
            printf("Failed to allocate memory");
            free(filename);
            return 8;
        }
    }
    else{
        printf("Unsupported file format");
        free(filename);
        return 7;
    }

    /* Drugi plik */

    printf("Podaj nazwę drugiego pliku: ");
    scanf("%19[^\n]", filename);
    while (getchar() != '\n');

    if(strlen(filename) <= 4){
        printf("Unsupported file format");
        matrix_destroy_struct(&m1);
        free(filename);
        return 7;
    }
    if(strcmp(filename + strlen(filename)- 4, ".bin") == 0){
        m2 = matrix_load_b(filename, &error);
        if(error == 2){
            printf("Couldn't open file");
            matrix_destroy_struct(&m1);
            matrix_destroy_struct(&m2);
            free(filename);
            return 4;
        }
        else if(error == 3){
            printf("File corrupted");
            matrix_destroy_struct(&m1);
            matrix_destroy_struct(&m2);
            free(filename);
            return 6;
        }
        else if(error == 4){
            printf("Failed to allocate memory");
            matrix_destroy_struct(&m1);
            free(filename);
            return 8;
        }
    }
    else if(strcmp(filename + strlen(filename)- 4, ".txt") == 0){
        m2 = matrix_load_t(filename, &error);
        if(error == 2){
            printf("Couldn't open file");
            matrix_destroy_struct(&m1);
            matrix_destroy_struct(&m2);
            free(filename);
            return 4;
        }
        else if(error == 3){
            printf("File corrupted");
            matrix_destroy_struct(&m1);
            matrix_destroy_struct(&m2);
            free(filename);
            return 6;
        }
        else if(error == 4){
            printf("Failed to allocate memory");
            matrix_destroy_struct(&m1);
            free(filename);
            return 8;
        }
    }
    else{
        printf("Unsupported file format");
        matrix_destroy_struct(&m1);
        free(filename);
        return 7;
    }

    struct matrix_t * sum_matrix = matrix_add(m1, m2);
    if(!sum_matrix) printf("Error\n");
    else matrix_display(sum_matrix);

    struct matrix_t * sub_matrix = matrix_subtract(m1, m2);
    if(!sub_matrix) printf("Error\n");
    else matrix_display(sub_matrix);

    struct matrix_t * mul_matrix = matrix_multiply(m1, m2);
    if(!mul_matrix) printf("Error\n");
    else matrix_display(mul_matrix);

    free(filename);
    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);
    matrix_destroy_struct(&sum_matrix);
    matrix_destroy_struct(&sub_matrix);
    matrix_destroy_struct(&mul_matrix);

    return 0;
}
