#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100000
#define THREADS 10

long count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

struct sum_thread{
    int *array;
    int id;
};

void *sum(void* arr){
    struct sum_thread *array = arr;
    for(int i = 0; i < SIZE/THREADS; ++i) {
        pthread_mutex_lock(&count_mutex);
        count += *(array->array + SIZE / THREADS * array->id + i);
        pthread_mutex_unlock(&count_mutex);
//        usleep(1);
    }

    return NULL;
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
    for(int i = 0; i < THREADS; ++i)
        pthread_join(thread[i], NULL);

    // Wyświetlanie wyniku
    printf("Result = %ld", count);

    return 0;
}
