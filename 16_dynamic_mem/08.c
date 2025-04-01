#include <stdio.h>

#include "08_array.h"

int main() {
    struct array_t * array;
    int input;
    printf("Podaj pojemnoĹÄ tablicy: ");
    if(scanf(" %d", &input) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(input<1){
        printf("Incorrect input data");
        return 2;
    }
    if(array_create_struct(&array, input) != 0){
        printf("Failed to allocate memory");
        return 8;
    }

    while(1){
        printf("Co chcesz zrobic: ");
        if(scanf(" %d", &input) != 1){
            array_destroy_struct(&array);
            printf("Incorrect input");
            return 1;
        }
        if(input == 0){
            array_destroy_struct(&array);
            return 0;
        }

        else if(input == 1){
            printf("Podaj kolejne liczby, ktĂłre majÄ zostaÄ dodane do tablicy: ");
            while(1){
                if(scanf(" %d", &input) != 1){
                    array_destroy_struct(&array);
                    printf("Incorrect input");
                    return 1;
                }
                if(input == 0) break;
                if(array_push_back(array, input) != 0)break;

            }
            if(array->size == 0) printf("Buffer is empty\n");
            else if(array->size == array->capacity) {
                printf("Buffer is full\n");
                array_display(array);
                printf("\n");
            }
            else{
                array_display(array);
                printf("\n");
            }
        }

        else if(input == 2)
        {
            printf("Podaj kolejne liczby, ktĂłre majÄ zostaÄ usuniete do tablicy: ");
            while(1){
                if(scanf(" %d", &input) != 1){
                    array_destroy_struct(&array);
                    printf("Incorrect input");
                    return 1;
                }
                if(input == 0) break;
                array_remove_item(array, input);
            }
            if(array->size == 0) printf("Buffer is empty\n");
            else if(array->size == array->capacity) {
                printf("Buffer is full\n");
                array_display(array);
                printf("\n");
            }
            else{
                array_display(array);
                printf("\n");
            }
        }
        else
            printf("Incorrect input data\n");
    }
}
