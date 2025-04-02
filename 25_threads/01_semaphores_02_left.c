#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "02_left_sem"

int main(void) {

    // Włączanie semafora z wartością domyślną 0 i możliwością współdzielenia
    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0666, 0);
    if(sem == NULL){
        printf("Error");
        return 1;
    }

    printf("Oczekiwanie na reakcje.\n");
    int c = getc(stdin);
    (void)c;

    // Wyświetlenie znaku w programie lewym
    printf("Komunikat programu lewego.\n");

    // Wypuszczenie semafora
    sem_post(sem);

    // Czekanie na program prawy
    printf("Program prawy skonczyl dzialanie.\n");

    sem_close(sem);

    // Usunięcie semafora
    sem_unlink("02_left_sem");

    return 0;
}
