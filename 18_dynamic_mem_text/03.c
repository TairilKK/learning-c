#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "03_dictionary.h"

#define FILENAME_CAPACITY 40

#define DICTIONARY_CAPACITY 10

char * modifyFilename(char * s, char * add){
    int size = (int)strlen(s);
    char c0 = *(s + size - 4);
    char c1 = *(s + size - 3);
    char c2 = *(s + size - 2);
    char c3 = *(s + size - 1);

    strcpy(s + size - 4, add);

    size = (int)strlen(s);
    *(s + size + 0) = c0;
    *(s + size + 1) = c1;
    *(s + size + 2) = c2;
    *(s + size + 3) = c3;
    *(s + size + 4) = '\0';
    return s;
}

int main() {
    dictionary_display(NULL);
    char * filename = calloc(FILENAME_CAPACITY, sizeof (char));
    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwę pliku: ");
    scanf("%39[^\n]", filename);
    while(getchar() != '\n');

    int op;
    printf("Co chcesz teraz zrobić: ");
    if(scanf("%d", &op) != 1){
        printf("Incorrect input");
        free(filename);
        return 1;
    }
    while(getchar() != '\n');


    int error;
    struct dictionary_t *d;
    if(op == 1) {
        FILE *f = fopen(filename, "r");
        if(!f){
            printf("Couldn't open file");
            free(filename);
            return 4;
        }
        char * input = calloc(40, sizeof (char ));
        if(!input){
            printf("Failed to allocate memory");
            fclose(f);
            free(filename);
            return 8;
        }
        d = create_dictionary(DICTIONARY_CAPACITY, &error);
        if (error == 2) {
            printf("Failed to allocate memory");
            fclose(f);
            free(input);
            free(filename);
            return 8;
        }
        int ret;
        while ((ret = fscanf(f, " %39[A-Za-z]", input)) != EOF) {
            if (ret == 1) {
                error = dictionary_add_word(d, input);
                if (error == 2) {
                    printf("Failed to allocate memory");
                    fclose(f);
                    free(input);
                    free(filename);
                    destroy_dictionary(&d);
                    return 8;
                }
            } else {
                fseek(f, 1, SEEK_CUR);
            }
        }
        fclose(f);
        free(input);
    }
    else if (op == 0){
        d = load_dictionary_b(filename, &error);
        if (error == 4) {
            printf("Failed to allocate memory");
            free(filename);
            return 8;
        }
        else if (error == 3) {
            printf("File corrupted");
            free(filename);
            return 6;
        }
        else if (error == 2) {
            printf("Couldn't open file");
            free(filename);
            return 4;
        }
    }
    else{
        printf("Incorrect input data");
        free(filename);
        destroy_dictionary(&d);
        return 2;
    }

    char * f_occ = calloc(47, sizeof(char));
    if(!f_occ){
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    strcpy(f_occ, filename);
    f_occ = modifyFilename(f_occ, "_occ");
    dictionary_sort_occurence(d);
    error = save_dictionary_b(d, f_occ);
    if(error == 2)
        printf("Couldn't create file\n");
    else
        printf("File saved\n");


    strcpy(f_occ, filename);
    f_occ = modifyFilename(f_occ, "_alpha");
    dictionary_sort_alphabetically(d);
    error = save_dictionary_b(d, f_occ);
    if(error == 2)
        printf("Couldn't create file");
    else
        printf("File saved");

    free(filename);
    free(f_occ);
    destroy_dictionary(&d);
    return 0;
}
