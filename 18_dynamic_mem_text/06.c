#include <stdio.h>
#include <stdlib.h>

#include "06_numbers.h"

int main() {
    printf("Enter a number: ");

    unsigned long long a;
    if(scanf("%llu", &a) != 1){
        printf("Incorrect input");
        return 1;
    }
    char * number;
    int error = number_2_words(&number, a);
    if(error == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("%s", number);
    free(number);
    return 0;
}
