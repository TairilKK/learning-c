#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main() {

    char * text = calloc(1001, sizeof(char));
    if(!text){
        printf("Failed to allocate memory");
        return 8;
    }

    char * (**func)(const char *) = calloc(4, sizeof(char * (*)(const char *)));
    if(!func){
        printf("Failed to allocate memory");
        free(text);
        return 8;
    }
    *(func + 0) = lower_to_upper;
    *(func + 1) = upper_to_lower;
    *(func + 2) = reverse_letter;
    *(func + 3) = space_to_dash;

    int * array_int = calloc(4, sizeof(int));
    if(!array_int){
        printf("Failed to allocate memory");
        free(text);
        free(func);
        return 8;
    }
    printf("Podaj tekst do przeksztalcenia: ");
    int counter = 0;
    char c;
    while(counter < 1000 && (c = getchar()) != '\n'){
        *(text + counter) = c;
        counter++;
    }
    if(c != '\n')
        while (getchar()!='\n');

    printf("Podaj liczbe operacj do przeprowadzenia: ");
    if(scanf("%d", &counter) != 1){
        printf("Incorrect input");
        free(text);
        free(func);
        free(array_int);
        return 1;
    }
    if(counter < 2 || counter > 4){
        printf("Incorrect input data");
        free(text);
        free(func);
        free(array_int);
        return 2;
    }

    printf("Podaj wybrane operacje: ");
    for(int i = 0; i < counter; ++i){
        if(scanf("%d", (array_int + i)) != 1){
            printf("Incorrect input");
            free(text);
            free(func);
            free(array_int);
            return 1;
        }
        if(*(array_int + i) < 0 || *(array_int + i) > 3){
            printf("Incorrect input data");
            free(text);
            free(func);
            free(array_int);
            return 2;
        }
    }

    char ** res = NULL;
    if(counter > 2) {
            res = text_modifier(text, counter, *(func + *(array_int + 0)), *(func + *(array_int + 1)), *(func + *(array_int + 2)), *(func + *(array_int + 3)));
    } else {
        printf("Incorrect input data");
        free(text);
        free(func);
        free(array_int);
        return 2;
    }

    if(!res){
        printf("Failed to allocate memory");
        free(text);
        free(func);
        free(array_int);
        return 8;
    }

    for(int i = 0; *(res + i); printf("%s\n", *(res + i)), ++i);

    free(text);
    free(func);
    free(array_int);
    free_texts(res);

    return 0;
}
