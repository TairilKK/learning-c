#include <stdio.h>
#include "03_bit_set.h"

int main() {
    union bit_set p;
    printf("Podaj liczbe:");

    if(scanf("%hhu",&(p.u1))!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("%d %d %d %d %d %d %d %d",p.u1/2/2/2/2/2/2/2%2,p.u1/2/2/2/2/2/2%2,p.u1/2/2/2/2/2%2,p.u1/2/2/2/2%2,p.u1/2/2/2%2,p.u1/2/2%2,p.u1/2%2,p.u1%2);

    return 0;
}

