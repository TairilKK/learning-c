#include <stdio.h>
#include <stdlib.h>

#define WIERSZ 10
#define KOLUMNA 10

int main() {

    int **tab;

    tab = (int **) malloc(WIERSZ * sizeof(int*));

    if (tab == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    for (int i = 0; i < WIERSZ; i++) {
        *(tab + i) = (int *) malloc(KOLUMNA * sizeof(int));
        if (*(tab + i) == NULL) {
            for (int j = 0; j < i; j++)
                free(*(tab + j));
            free(tab);
            printf("Failed to allocate memory");
            return 8;
        }
    }

    for (int i = 0; i < WIERSZ; i++) {
        for (int j = 0; j < KOLUMNA; j++)
            *(*(tab + i) + j) = (i+1) * (j+1);
    }

    for (int i = 0; i < WIERSZ; i++) {
        for (int j = 0; j < KOLUMNA; j++)
            printf("%3d ", *(*(tab + i) + j));
        printf("\n");
    }

    for (int i = 0; i < WIERSZ; i++)
        free(*(tab + i));
    free(tab);

    return 0;
}