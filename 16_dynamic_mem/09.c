#include <stdio.h>
#include <stdlib.h>

#include "09_circular_buffer.h"


int main() {
    struct circular_buffer_t * cb;
    int N;

    printf("Podaj rozmiar bufora: ");
    if(scanf(" %d", &N) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(N<1){
        printf("Incorrect input data");
        return 2;
    }
    if (circular_buffer_create_struct(&cb, N) != 0){
        printf("Failed to allocate memory");
        return 8;
    }

    while(1){
        printf("Co chcesz zrobic? ");
        if(scanf(" %d", &N) != 1){
            printf("Incorrect input");
            circular_buffer_destroy_struct(&cb);
            return 1;
        }
        if(N == 0){
            circular_buffer_destroy_struct(&cb);
            return 0;
        }
        else if(N == 1){
            printf("Podaj liczbe: ");
            if(scanf(" %d", &N) != 1){
                printf("Incorrect input");
                circular_buffer_destroy_struct(&cb);
                return 1;
            }
            circular_buffer_push_back(cb, N);
        }
        else if(N == 2){
            if(circular_buffer_empty(cb)!=0)
                printf("Buffer is empty\n");
            else
                printf("%d\n",circular_buffer_pop_back(cb, NULL));
        }
        else if(N == 3){
            if(circular_buffer_empty(cb)!=0)
                printf("Buffer is empty\n");
            else
                printf("%d\n",circular_buffer_pop_front(cb, NULL));
        }
        else if(N == 4){
            if(circular_buffer_empty(cb)!=0)
                printf("Buffer is empty");
            else
                circular_buffer_display(cb);
            printf("\n");
        }
        else if(N == 5){
            printf("%d\n",(circular_buffer_empty(cb) != 0) ? 1 : 0);
        }
        else if(N == 6){
            printf("%d\n",(circular_buffer_full(cb) != 0) ? 1 : 0);
        }
        else
            printf("Incorrect input data\n");
    }


}
