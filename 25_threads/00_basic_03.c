#include <stdio.h>
#include <pthread.h>

#define THREAD_NUMBER 10

void *display(void* arg){
    int id = *((int*)arg);
    printf("Hello jestem watkiem nr: %d\n", id);
    return NULL;
}

int main(void) {

    // Tablica przechowująca wątki
    pthread_t thread[THREAD_NUMBER];

    // Tablica przechowująca ID wątków
    int thread_id[THREAD_NUMBER];
    for(int i = 0; i < THREAD_NUMBER; ++i)
        thread_id[i] = i;

    // Utworzenie wątków, które wykonają funkcję display
    for(int i = 0; i < THREAD_NUMBER; ++i)
        pthread_create(thread+i, NULL, display, thread_id+i);

    // Oczekiwanie na koniec pracy wszystkich wątków
    for(int i = 0; i < THREAD_NUMBER; ++i)
        pthread_join(thread[i], NULL);

    return 0;
}
