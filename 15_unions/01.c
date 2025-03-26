#include <stdio.h>
#include "01_byte_set.h"

int main() {
    union byte_set p;
    printf("Podaj liczbe:");

    if(scanf("%d",&(p.u1))!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("%d %d %d %d",*(p.u2),*(p.u2+1),*(p.u2+2),*(p.u2+3));

    return 0;
}

