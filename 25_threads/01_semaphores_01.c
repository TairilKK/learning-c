#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define SIZE 100000
#define THREADS 10

long count = 0;

// Globalna zmienna na semafor
sem_t count_sem;

struct sum_thread{
    int *array;
    int id;
};

void *sum(void* arr){
    struct sum_thread *array = arr;
    for(int i = 0; i < SIZE/THREADS; ++i) {
        sem_wait(&count_sem); // -1
        count += *(array->array + SIZE / THREADS * array->id + i);
        sem_post(&count_sem); // +1
        usleep(1);
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

    // Inicjalizacja semafora z wartością 1
    if(sem_init(&count_sem, 0, 1) != 0){
        printf("error: sem_init");
        return 1;
    }

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

    // Zwalnianie zasobów
    sem_destroy(&count_sem);

    return 0;
}
