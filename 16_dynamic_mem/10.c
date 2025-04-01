#include <stdio.h>

#include "vector.h"

int main() {
    int input, r;
    struct vector_t *a;

    printf("Podaj pojemność tablicy: ");
    if(scanf(" %d", &input) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(input < 1){
        printf("Incorrect input data");
        return 2;
    }
    r = vector_create_struct(&a, input);
    if(r == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    input = 3;
    while(input != 0){
        printf("Co chcesz zrobic: ");
        if(scanf("%d", &input) != 1){
            printf("incorrect input");
            vector_destroy_struct(&a);
            return 1;
        }
        if(input == 0)
            break;

        else if( input == 1 ){
            printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
            while(input != 0){
                if(scanf(" %d", &input) != 1) {
                    printf("incorrect input");
                    vector_destroy_struct(&a);
                    return 1;
                }
                if(input != 0)
                    r = vector_push_back(a, input);
                if(r == 2){
                    printf("Failed to allocate memory\n");
                    break;
                }
            }
            input = 1;
        }
        else if ( input == 2 ){
            printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
            while(input != 0){
                if(scanf("%d", &input) != 1) {
                    printf("incorrect input");
                    vector_destroy_struct(&a);
                    return 1;
                }
                vector_erase(a, input);
            }
            input = 2;
        }
        else if( input > 2 )
            printf("Incorrect input data\n");

        if(input != 0 && input < 3) {
            if (a->size == 0)printf("Buffer is empty\n");
            else{
                vector_display(a);
                printf("\n");
            }
        }
    }

    vector_destroy_struct(&a);
    return 0;
}