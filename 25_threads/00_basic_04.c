#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000
#define THREADS 10

struct sum_thread{
    int *array;
    int id;
};

void *sum(void* arr){
    struct sum_thread *array = arr;

    long *result = malloc(sizeof(long));
    if(result == NULL)
        return NULL;
    *result = 0;

    for(int i = 0; i < SIZE/THREADS; ++i)
        *result += *(array->array + SIZE/THREADS* array->id + i);

    return (void*)result;
}

int main(void) {

    // Tablica wątków
    pthread_t thread[THREADS];

    // Tablica liczb do zsumowania
    int tab[SIZE];
    for(int i = 0; i < SIZE; i++)
        tab[i] = i;

    // Utworzenie wątków, które wykonają funkcję display
    struct sum_thread array[THREADS];
    for(int i = 0; i < THREADS; ++i) {
        array[i].array = tab;
        array[i].id = i;
        pthread_create(thread + i, NULL, sum, &array[i]);
    }

    // Oczekiwanie na koniec pracy wszystkich wątków
    long* sub_result[THREADS];
    for(int i = 0; i < THREADS; ++i)
        pthread_join(thread[i], (void **)(sub_result + i));

    // Dodanie ostatecznego wyniku
    long result = 0;
    for(int i = 0; i < THREADS; ++i)
        result += *(sub_result[i]);
    printf("Result = %ld", result);

    // Zwalnianie pamięci zaalokowanej przez wątki
    for(int i = 0; i < THREADS; ++i)
        free(sub_result[i]);

    return 0;
}
