#include <stdio.h>
#include <pthread.h>

void *display(void* arg){
    (void)arg;

    printf("Hello\n");
    return NULL;
}

int main(void) {

    // Zmienna przechowująca wątek
    pthread_t thread;

    // Utworzenie wątku, który wykona funkcję display
    pthread_create(&thread, NULL, display, NULL);

    // Oczekiwanie na koniec pracy wątku
    pthread_join(thread, NULL);

    return 0;
}
