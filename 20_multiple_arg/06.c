#include <stdio.h>

#include "06_function.h"

int main() {
    printf("%llu\n", bits_to_number(NULL, 3, 1,1,1));
    printf("%llu\n", bits_to_number(NULL, 8, 1,0,0,0,0,0,0,1));
    printf("%llu\n", bits_to_number(NULL, 32, 1,1,0,1,0,0,0,1, 0,0,0,0,1,1,0,1, 0,1,0,0,1,0,1,1, 1,1,1,0,1,1,1,0));
    return 0;
}
