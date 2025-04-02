#include <stdio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#include "03_common.h"

int main() {
    pthread_t pthread;

    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0666, 0);
    if(sem == NULL){
        printf("SEM error");
        return 1;
    }

    int fd = shm_open(SHM_NAME, O_RDWR | O_CREAT |O_EXCL, 1);
    if(fd == -1){
        sem_unlink(SEM_NAME);
        printf("SHM error");
        return 2;
    }

    if(ftruncate(fd, sizeof(struct payload_t)) != 0){
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        printf("ftruncate error");
        return 3;
    }

    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);
    return 0;
}
