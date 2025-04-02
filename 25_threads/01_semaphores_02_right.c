#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define SEM_NAME "02_left_sem"

int main(void) {

    // Włączanie semafora z wartością domyślną 0 i możliwością współdzielenia
    sem_t *sem = sem_open(SEM_NAME, 0);
    if(sem == NULL){
        printf("Error");
        return 1;
    }

    printf("Czekam na reakcje uzytkownika w programie 01_semaphores_02_left.\n");
    sem_wait(sem);

    // Wyświetlenie znaku w programie lewym
    printf("Komunikat programu prawego.\n");

    return 0;
}
