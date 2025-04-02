#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include "04_common.h"

int main() {

    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);

    printf("Uruchomiono serwer obliczeniowy.\n");

    int fd = shm_open(SHM_NAME, O_RDWR | O_EXCL | O_CREAT, 0666);
    printf("Utworzono polaczenie.\n");

    sem_t *server_ready = sem_open(SEM_NAME, O_CREAT | O_EXCL, 1, 0);
    printf("Utworzono semafor.\n");

    int status = ftruncate(fd, sizeof(struct calc_t));
    printf("Przydzielenie pamieci wspoldzielonej.\n");

    struct calc_t *pcalc = mmap(NULL, sizeof(struct calc_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_init(&pcalc->result_ready, 1, 0);
    sem_init(&pcalc->data_ready, 1, 0);

    printf("Struktura komunikacyjna zmapowana.\n");
    sem_post(server_ready);
    while(1) {

        printf("Oczekiwanie na dane od klienta...\n");
        sem_wait(&pcalc->data_ready);

        printf("Otrzymano dane. Liczenie rozpoczete.\n");

        switch (pcalc->op) {
            case '+':
                pcalc->result = pcalc->a + pcalc->b;
                break;

            case '-':
                pcalc->result = pcalc->a - pcalc->b;
                break;

            case '*':
                pcalc->result = pcalc->a * pcalc->b;
                break;

            case '/':
                if (pcalc->b == 0) {
                    pcalc->result = 0;
                    break;
                }
                pcalc->result = pcalc->a / pcalc->b;
                break;
        }

        printf("Liczenie ukonczone.\n");
        sem_post(&pcalc->result_ready);

        printf("Czy zakonczyc dzialanie programu?(t/n)");
        if (scanf("%c", &pcalc->quit) != 1) {
            printf("Error");
            return 1;
        }
        while (getchar() != '\n');

        if(pcalc->quit == 't') {
            printf("Wylaczanie serwera.\n");
            break;
        }
    }

    printf("Zwalnianie zasobow.\n");
    sem_destroy(&pcalc->data_ready);
    sem_destroy(&pcalc->result_ready);

    munmap(pcalc, sizeof(struct calc_t));
    close(fd);
    shm_unlink(SHM_NAME);

    sem_close(server_ready);
    sem_unlink(SEM_NAME);

    return 0;
}
