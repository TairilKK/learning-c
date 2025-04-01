#include <stdio.h>
#include <stdlib.h>

#include "02_dictionary.h"

#define FILENAME_CAPACITY 50

#define DICTIONARY_CAPACITY 10

int main() {
    char * input = calloc(FILENAME_CAPACITY, sizeof (char));
    if(!input){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwę pliku: ");
    scanf("%49[^\n]", input);
    while(getchar() != '\n');

    FILE *f = fopen(input, "r");
    if(!f){
        printf("Couldn't open file");
        free(input);
        return 4;
    }

    int error;
    struct dictionary_t * d = create_dictionary(DICTIONARY_CAPACITY, &error);

    if(error == 2){
        printf("Failed to allocate memory");
        fclose(f);
        free(input);
        return 8;
    }

    int ret;
    while((ret = fscanf(f," %49[A-Za-z]", input)) != EOF){
        if (ret == 1) {
            error = dictionary_add_word(d, input);
            if (error == 2) {
                printf("Failed to allocate memory");
                fclose(f);
                free(input);
                destroy_dictionary(&d);
                return 8;
            }
        } else {
            fseek(f, 1, SEEK_CUR);
        }
    }
    if(d->size==0)
        printf("Nothing to show");
    dictionary_display(d);

    fclose(f);
    free(input);
    destroy_dictionary(&d);

    return 0;
}
