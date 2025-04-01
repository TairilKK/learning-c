#include <stdio.h>
#include <stdlib.h>

#include "08_functions.h"

DEFINE_ARRAY(int)
CREATE_ARRAY(int)
FREE_ARRAY(int)
SAVE_ARRAY(int)
LOAD_ARRAY(int)
SORT_ARRAY(int)

DEFINE_ARRAY(double)
CREATE_ARRAY(double)
FREE_ARRAY(double)
SAVE_ARRAY(double)
LOAD_ARRAY(double)
SORT_ARRAY(double)


int main() {
    struct array_int_t * arrayInt;
    struct array_double_t * arrayDouble;

    char * filename;
    filename = calloc(31, sizeof(char));
    if(filename == NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter filename: ");
    scanf("%30[^\n]c", filename);
    while(getchar()!='\n');

    int type;
    printf("Choose your type:");
    if(scanf("%d", &type)!=1){
        printf("Incorrect input");
        free(filename);
        return 1;
    }
    if(type<0 || type>1){
        printf("Incorrect input data");
        free(filename);
        return 2;
    }
    int res;
    if(type == 0){
        res = load_array_int(&arrayInt, filename);
        if(res == 2){
            printf("Couldn't open file");
            free(filename);
            return 4;
        } else if(res == 3){
            printf("File corrupted");
            free(filename);
            return 6;
        }else if(res == 4){
            printf("Failed to allocate memory");
            free(filename);
            return 8;
        }
        sort_array_int(arrayInt);
        res = save_array_int(arrayInt, filename);
        if(res == 2){
            printf("Couldn't create file");
            free(filename);
            free_array_int(arrayInt);
            return 5;
        }
        free_array_int(arrayInt);
    }
    else{
        res = load_array_double(&arrayDouble, filename);
        if(res == 2){
            printf("Couldn't open file");
            free(filename);
            return 4;
        } else if(res == 3){
            printf("File corrupted");
            free(filename);
            return 6;
        }else if(res == 4){
            printf("Failed to allocate memory");
            free(filename);
            return 8;
        }
        sort_array_double(arrayDouble);
        res = save_array_double(arrayDouble, filename);
        if(res == 2){
            printf("Couldn't create file");
            free(filename);
            free_array_double(arrayDouble);
            return 5;
        }
        free_array_double(arrayDouble);
    }
    free(filename);
    printf("File saved");

    return 0;
}
