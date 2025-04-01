#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "01_big_numbers.h"

#define BUFFER_CAPACITY 201
#define BIG_NUMBERS_CAPACITY 10

int main() {

    /* Tworzenie struktury BIG_NUMBERS_T */
    struct big_numbers_t * bn;
    int error = create_big_numbers(&bn, BIG_NUMBERS_CAPACITY);
    if(error == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    /* Tworzenie bufferu na input */
    char * buffer = calloc(BUFFER_CAPACITY, sizeof(char));
    if(!buffer){
        printf("Failed to allocate memory\n");
        destroy_big_numbers(&bn);
        return 8;
    }

    /* Wczytywanie liczb */
    char c;
    int i = 0;
    printf("Podaj liczby: ");
    while(1){
        while ((c = getchar()) != '\n' && i < (BUFFER_CAPACITY - 1)) {
            *(buffer + i) = c;
            *(buffer + i + 1) = '\0';
            i++;
        }
        if(c == '\n' && i == 0)
            break;
        if (c != '\n')
            while (getchar() != '\n');

        i = 0;

        error = add_big_number(bn, buffer);
        if (error == 1)
            printf("Incorrect input\n");
        else if (error == 2) {
            printf("Failed to allocate memory\n");
            break;
        }
        else if (error == 3) {
            printf("Buffer is full\n");
            break;
        }
    }

    if(bn->size == 0)
        printf("Buffer is empty");
    display(bn);

    /* Zwalnianie zasobów */
    destroy_big_numbers(&bn);
    free(buffer);
    return 0;
}
