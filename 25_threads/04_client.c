#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include "04_common.h"

int main() {

    char op, quit, operators[] = "+-*/";
    int check = 0;
    double a, b;
    struct calc_t *pcalc = NULL;

    sem_t *sem_server = sem_open(SEM_NAME, 0);

    printf("Oczekiwanie na serwer...\n");
    sem_wait(sem_server);

    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if(fd == -1){
        printf("Error");
        return 2;
    }

    while(1) {
        printf("Podaj liczbe A:");
        if (scanf("%lf", &a) != 1) {
            printf("Error\n");
            continue;
        }
        while (getchar() != '\n');

        printf("Podaj liczbe B:");
        if (scanf("%lf", &b) != 1) {
            printf("Error\n");
            continue;
        }
        while (getchar() != '\n');

        printf("Wybierz operacje, ktora chcesz wykonac (+,-,*,/):");
        if (scanf("%c", &op) != 1) {
            printf("Error\n");
            continue;
        }
        while (getchar() != '\n');

        for (int i = 0; i < strlen(operators); ++i) {
            if (op == operators[i])
                check++;
        }

        if (check == 0) {
            printf("Error\n");
            continue;
        }

        pcalc = mmap(NULL, sizeof(struct calc_t), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
        pcalc->a = a;
        pcalc->b = b;
        pcalc->op = op;

        sem_post(&pcalc->data_ready);

        printf("Oczekiwanie na odpowiedz serwera...\n");
        sem_wait(&pcalc->result_ready);

        printf("Wynik: %lf %c %lf = %lf\n", pcalc->a, pcalc->op, pcalc->b, pcalc->result);

        printf("Czy zakonczyc dzialanie programu?(t/n)");
        if (scanf("%c", &quit) != 1) {
            printf("Error");
            return 1;
        }
        while (getchar() != '\n');
        pcalc->quit = quit;
        sem_post(&pcalc->data_ready);

        if(quit == 't')
            break;
    }

    return 0;
}
