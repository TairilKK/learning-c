#include <stdio.h>
#include <pthread.h>

#define THREAD_NUMBER 10

void *display(void* arg){
    (void)arg;

    printf("Hello\n");
    return NULL;
}

int main(void) {

    // Tablica przechowująca wątki
    pthread_t thread[THREAD_NUMBER];

    // Utworzenie wątków, które wykonają funkcję display
    for(int i = 0; i < THREAD_NUMBER; ++i)
        pthread_create(thread+i, NULL, display, NULL);

    // Oczekiwanie na koniec pracy wszystkich wątków
    for(int i = 0; i < THREAD_NUMBER; ++i)
        pthread_join(thread[i], NULL);

    return 0;
}
