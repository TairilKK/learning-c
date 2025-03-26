#include <stdio.h>

#include "06_complex_t.h"

int main() {
    float re, im;
    char temp;
    struct complex_t a, b;

    printf("Enter a complex number: ");
    if(scanf("%f%ci%f", &re, &temp, &im) != 3)
    {
        printf("Incorrect input");
        return 1;
    }
    if(im < 0)
    {
        printf("Incorrect input");
        return 1;
    }
    if(temp == '+') set(&a, re, im, NULL);
    else if(temp == '-') set(&a, re, -im, NULL);
    else
    {
        printf("Incorrect input");
        return 1;
    }
    temp = 'x';

    printf("Enter a complex number: ");
    if(scanf("%f%ci%f", &re, &temp, &im) != 3)
    {
        printf("Incorrect input");
        return 1;
    }
    if(im < 0)
    {
        printf("Incorrect input");
        return 1;
    }
    if(temp == '+') set(&b, re, im, NULL);
    else if(temp == '-') set(&b, re, -im, NULL);
    else
    {
        printf("Incorrect input");
        return 1;
    }
    show(&a);
    printf("\n");

    show(&b);
    printf("\n");

    float abs = complex_abs(&a, NULL);
    abs -= complex_abs(&b, NULL);

    if(abs < 0) printf("SECOND");
    else if(abs == 0) printf("EQUAL");
    else printf("FIRST");

    return 0;
}

