//
// Created by root on 1/5/25.
//

#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include <semaphore.h>
#include <pthread.h>

#define SHM_NAME "shm_kol"
#define SEM_NAME "sem_kol"

struct calc_t{
    char op, quit;
    int is_error;
    double a, b, result;
    sem_t result_ready, data_ready;
};

struct sh_data_t{
    char old_c, new_c;
    char shm_name[30];
    int error;
    size_t length;
    sem_t result_ready, data_ready;
};

#endif //SERVER_COMMON_H
