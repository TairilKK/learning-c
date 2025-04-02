#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "03_common.h"

int main() {
    char op;
    double a, b, result;
    printf("Podaj piersza liczbe:");
    if(scanf("%lf", &a) != 1){
        printf("Incorrect input");
        return 1;
    }
    while(getchar() != '\n');

    printf("Podaj operajce:");
    op = (char)getchar();

    printf("Podaj druga liczbe:");
    if(scanf("%lf", &b) != 1){
        printf("Incorrect input");
        return 1;
    }
    while(getchar() != '\n');

    printf("%lf %lf %c", a, b, op);

    sem_t *sem = sem_open(SEM_NAME, 0);
    if(sem == NULL){
        printf("SEM error");
        return 1;
    }

    sem_wait(sem);
    int fd = shm_open(SHM_NAME, O_RDWR, 0);
    if(fd == -1){
        printf("SHM error");
        sem_post(sem);
        return 2;
    }
    struct payload_t payload = {a, b, op};

    return 0;
}
