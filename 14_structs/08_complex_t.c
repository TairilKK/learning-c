//
// Created by jdobr on 17.08.2023.
//
#include <stdio.h>
#include <math.h>

#include "08_complex_t.h"


struct complex_t* set(struct complex_t* cp, float re, float im, int *err_code)
{
    if(cp == NULL) { ERROR(1);  return NULL; }
    cp->re = re;
    cp->im = im;
    ERROR(0);
    return cp;
}

float complex_abs(struct complex_t* cp, int * err_code)
{
    if(cp == NULL) { ERROR(1); return -1.0f; }
    ERROR(0);
    return sqrtf((cp->re) * (cp->re) + (cp->im) * (cp->im));
}

void show(const struct complex_t* cp)
{
    if(cp == NULL) return;
    cp->im > 0 ? printf("%f + i%f", cp->re, cp->im) : printf("%f - i%f", cp->re, -(cp->im));
}



int read(struct complex_t* cp){
    if(cp == NULL) return 1;
    float re, im;
    char temp;

    if(scanf("%f%ci%f", &re, &temp, &im) != 3) return 2;

    if(im < 0) return 2;

    if(temp == '+') set(cp, re, im, NULL);
    else if(temp == '-') set(cp, re, -im, NULL);
    else return 2;

    return 0;
}


int add(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    return (first == NULL || second == NULL || result == NULL) ? 1 : ((result->re = first->re + second->re, result->im = first->im + second->im), 0);
}

int subtract(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    return (first == NULL || second == NULL || result == NULL) ? 1 : ((result->re = first->re - second->re, result->im = first->im - second->im), 0);
}


int multiply(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    return (first == NULL || second == NULL || result == NULL) ? 1 : ((result->re = (first->re * second->re - first->im * second->im), result->im = (first->re * second->im + first->im*second->re)), 0);
}


int divide(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    return (first == NULL || second == NULL || result == NULL) ? 1 : ((second->re == 0 && second->im == 0) ? 2 : ((result->re = (first->re * second->re + first->im * second->im)/(second->re * second->re + second->im * second->im), result->im = (first->im * second->re - first->re * second->im)/(second->re * second->re + second->im * second->im)), 0));
}

