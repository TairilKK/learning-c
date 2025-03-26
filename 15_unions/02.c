#include <stdio.h>
#include "02_word_set.h"

int main() {
    union word_set p;
    printf("Podaj liczbe:");

    if(scanf("%d",&(p.u1))!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("%d %d",*(p.u2),*(p.u2+1));

    return 0;
}

