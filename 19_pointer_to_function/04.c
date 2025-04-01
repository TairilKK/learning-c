#include <stdio.h>
#include <stdlib.h>

#include "04_char_operations.h"

int main() {
    char (**func)(char) = calloc(4, sizeof(char (*)(char)));
    if(func == NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    *(func + 0) = lower_to_upper;
    *(func + 1) = upper_to_lower;
    *(func + 2) = space_to_dash;
    *(func + 3) = reverse_letter;

    char * input;
    input = calloc(1001, sizeof(char));

    if(input == NULL){
        printf("Failed to allocate memory");
        free(func);
        return 8;
    }

    printf("Podaj tekst: ");
    scanf("%1000[^\n]c", input);
    while(getchar() != '\n');
    int op;

    printf("Podaj rodzaj operacji: ");
    if(scanf("%d", &op) != 1){
        printf("Incorrect input");
        free(func);
        free(input);
        return 1;
    }
    if(op < 0 || op > 3){
        printf("Incorrect input data");
        free(func);
        free(input);
        return 2;
    }

    char * b = letter_modifier(input, *(func + op));
    if(b == NULL){
        printf("Failed to allocate memory");
        free(func);
        free(input);
        return 8;
    }

    printf("%s", b);

    free(func);
    free(input);
    free(b);

    return 0;
}
