#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

#define SEM_NAME "shared_memory_01_left_sem"
#define SHM_NAME "shared_memory_01_left_shm"

struct data_t {
    sem_t cs;
    int payload;
};

int main(void) {


    sem_t *sem = sem_open(SEM_NAME, 0);
    if(sem == NULL){
        printf("Error: %s", SEM_NAME);
        return 1;
    }

    // Otwieram obiekt pamięci współdzielonej
    int fd = shm_open(SHM_NAME, O_RDWR, 0);
    if(fd == -1){
        printf("Error: %s", SHM_NAME);
        return 1;
    }

    printf("Czekam na shared_memory_01_left_sem.c\n");
    sem_wait(sem);

    struct data_t *ptr = (struct data_t*) mmap(NULL, sizeof(struct data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        printf("Error: %s", "MAP_FAILED");
        return 1;
    }

    // Wyświetlenie znaku
    printf("Wartość: %d\n", ptr->payload);
    sem_post(&ptr->cs);

    return 0;
}
