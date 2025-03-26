#include <stdio.h>

#include "08_complex_t.h"

int main() {
    struct complex_t a = {0, 0}, b = {0, 0}, res = {0, 0};
    complex_abs(&a, NULL);
    printf("Enter a complex number: ");
    if (read(&a) != 0)
    {
        printf("Incorrect input");
        return 1;
    }

    printf("Enter a complex number: ");
    if (read(&b) != 0)
    {
        printf("Incorrect input");
        return 1;
    }

    add(&a, &b, &res);
    show(&res);
    printf("\n");

    subtract(&a, &b, &res);
    show(&res);
    printf("\n");

    multiply(&a, &b, &res);
    show(&res);
    printf("\n");

    if(divide(&a, &b, &res) == 0) show(&res);
    else printf("Operation not permitted");
    printf("\n");

    return 0;
}

