//
// Created by jdobr on 17.08.2023.
//
#include <stdio.h>
#include <math.h>

#include "06_complex_t.h"


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
    cp->im > 0 ? printf("%.2f + i%.2f", cp->re, cp->im) : printf("%.2f - i%.2f", cp->re, -(cp->im));
}
