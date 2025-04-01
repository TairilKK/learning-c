#include <stdio.h>

#include "07_array.h"


int main() {
    struct array_t src, even = {.size = 0 }, odd = {.size = 0 };
    int size, input;

    printf("Podaj liczbÄ elementĂłw tablicy: ");
    if(scanf(" %d", &size) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(size < 1){
        printf("Incorrect input data");
        return 2;
    }
    if(array_create(&src, size) != 0){
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj kolejne liczby, ktĂłre majÄ zostaÄ dodane do tablicy: ");
    while(1){
        if(scanf(" %d", &input) != 1){
            printf("Incorrect input");
            array_destroy(&src);
            return 1;
        }
        if(input == 0)
            break;
        if(src.size == src.capacity) {
            printf("Buffer is full\n");
            break;
        }

        array_push_back(&src, input);
    }

    if(src.size == 0){
        printf("Not enough data available");
        array_destroy(&src);
        return 3;
    }

    if(array_separate(&src, &odd, &even) == 0){
        array_destroy(&src);
        printf("Failed to allocate memory");
        return 8;
    }


    if(odd.size == 0) printf("Buffer is empty");
    array_display(&odd);
    printf("\n");

    if(even.size == 0) printf("Buffer is empty");
    array_display(&even);

    array_destroy(&src);
    array_destroy(&odd);
    array_destroy(&even);

    return 0;
}
