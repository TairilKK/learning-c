#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "shared_memory_01_left_sem"
#define SHM_NAME "shared_memory_01_left_shm"

struct data_t {
    sem_t cs;
    int payload;
};

int main(void) {

    // Wartość do wysłania
    int value = 123;

    // Stworzenie i otwarcie semafora nazwanego
    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 1, 0);
    if(sem == NULL){
        printf("Error: %s", SEM_NAME);
        return 1;
    }

    // Otwieram obiekt pamięci współdzielonej
    int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(fd == -1){
        sem_unlink(SEM_NAME);
        printf("Error: %s", SHM_NAME);
        return 1;
    }

    // Określam długość obiektu do wysłania
    if(ftruncate(fd, sizeof(struct data_t)) == -1){
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        printf("Error: %s", "ftruncate");
        return 1;
    }

    struct data_t *ptr = (struct data_t*)mmap(NULL, sizeof(struct data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED){
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        printf("Error: %s", "MAP_FAILED");
        return 1;
    }
    sem_init(&ptr->cs, 1, 0);
    ptr->payload = value;

    sem_post(sem);
    sem_wait(&ptr->cs);

    printf("Czkam na wlaczenie programu: 02_shared_memory_01_right.c\n");

    // Zwalnianie zasobów
    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);

    return 0;
}
