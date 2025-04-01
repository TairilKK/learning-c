#include <stdio.h>
#include <stdint.h>

#define DISPLAY_BITS(value) \
do{                        \
    for(int i = sizeof(value) * 8 - 1; i >= 0; --i) \
        printf("%d", ((value) & (1ULL << i) ? 1 : 0));    \
    printf("\n");\
}while(0)


int main() {
    uint64_t input;
    printf("Podaj liczbę 64 bitową: ");
    if(scanf("%lu", &input) != 1){
        printf("Incorrect input");
        return 1;
    }
    DISPLAY_BITS(input);
    return 0;
}
