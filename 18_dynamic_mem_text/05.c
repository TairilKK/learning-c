#include <stdio.h>
#include <stdlib.h>

#include "05_maze.h"

int main() {
    char ** m = NULL;
    int error;

    char * filename = calloc(31, sizeof(char));
    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter filename: ");
    scanf("%30[^\n]", filename);
    while(getchar() != '\n');

    error = load_maze(filename, &m);
    if(error == 2){
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    else if(error == 3){
        printf("File corrupted");
        free(filename);
        return 6;
    }
    else if(error == 4){
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    /* Sprawdzanie czy jest B */
    int flagB = 0;
    for(int i = 0; *(m + i) != NULL; ++i) {
        for(int j = 0; *(*(m + i) + j) != '\0'; ++j)
            if(*(*(m + i) + j) == 'b')
                flagB += 1;
    }
    if(flagB != 1){
        printf("File corrupted");
        free(filename);
        free_maze(m);
        return 6;
    }
    /* Sprawdzanie czy jest A */
    int xA = 0, yA = 0;
    int flagA = 0;
    for(int i = 0; *(m + i) != NULL; ++i) {
        for(int j = 0; *(*(m + i) + j) != '\0'; ++j)
            if(*(*(m + i) + j) == 'a') {
                xA = j;
                yA = i;
                flagA += 1;
            }
    }
    if(flagA != 1){
        printf("File corrupted");
        free(filename);
        free_maze(m);
        return 6;
    }

    error = solve_maze(m, xA, yA);
    if(error == 0)
        printf("Couldn't find path");
    else {
        for (int i = 0; *(m + i) != NULL; printf("\n"), ++i)
            for (int j = 0; *(*(m + i) + j) != '\0'; printf("%c", *(*(m + i) + j)), ++j);
    }

    free(filename);
    free_maze(m);
    return 0;
}
