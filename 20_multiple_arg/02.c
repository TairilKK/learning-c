#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int concatenate(char *buffer, int buff_capacity, int number, ...){
    if(buffer==NULL || number <=0 || buff_capacity<=0)
        return 1;

    char *word;
    int j=0, k=0;
    for(int i=0; i < buff_capacity; ++i)
        *(buffer + i) = 0;


    va_list args;
    va_start(args, number);

    for(int i=0; i < number; ++i) {
        if (j >= buff_capacity - 1) {
            va_end(args);
            return 2;
        }

        word = va_arg(args, char*);

        if (i != 0) {
            *(buffer + j) = ' ';
            ++j;
        }
        while(*(word + k)!=0) {
            *(buffer + j) = *(word + k);
            ++k;
            ++j;
        }
        k=0;
    }
    if(j>=buff_capacity){
        va_end(args);
        return 2;
    }
    va_end(args);
    return 0;
}

void destroy_array(char **ptr, int size){
    if(ptr==NULL)
        return;
    if(*ptr==NULL) {
        free(ptr);
        return;
    }
    for(int i = 0; i<size; ++i)
        if(*(ptr+i)!=NULL)
            free(*(ptr+i));
    if(ptr!=NULL)
        free(ptr);
}

int main() {
    int number;
    char **input;
    char *res;

    input = calloc(4, sizeof (char *));

    if(input == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i=0; i<4; ++i){
        *(input + i)=calloc(1001, sizeof(char));
        if(*(input + i) == NULL) {
            destroy_array(input, 4);
            printf("Failed to allocate memory");
            return 8;
        }
    }
    res = calloc(4004,sizeof (char));

    if(res == NULL) {
        destroy_array(input, 4);
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczbe tekstow do wprowadzenia: ");

    if(scanf("%d", &number) != 1){
        printf("Incorrect input");
        destroy_array(input, 4);
        free(res);
        return 1;
    }
    if(number > 4 || number <= 1){
        printf("Incorrect input data");
        destroy_array(input, 4);
        free(res);
        return 2;
    }

    printf("Podaj teksty: ");
    for(int i=0; i < number; ++i) {
        while(getchar()!='\n');
        scanf("%1000[^\n]s", *(input + i));
    }

    concatenate(res, 4001, number, *input, *(input + 1), *(input + 2), *(input + 3));
    printf("%s", res);
    destroy_array(input, 4);
    free(res);

    return 0;
}
