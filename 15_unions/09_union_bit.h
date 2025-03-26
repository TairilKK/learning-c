//
// Created by jdobr on 19.08.2023.
//

#ifndef INC_11_UNION_BIT_H
#define INC_11_UNION_BIT_H

#include <stdio.h>
#include <stdint.h>

struct bits32
{
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
    unsigned char bit8 : 1;
    unsigned char bit9 : 1;
    unsigned char bit10 : 1;
    unsigned char bit11 : 1;
    unsigned char bit12 : 1;
    unsigned char bit13 : 1;
    unsigned char bit14 : 1;
    unsigned char bit15 : 1;
    unsigned char bit16 : 1;
    unsigned char bit17 : 1;
    unsigned char bit18 : 1;
    unsigned char bit19 : 1;
    unsigned char bit20 : 1;
    unsigned char bit21 : 1;
    unsigned char bit22 : 1;
    unsigned char bit23 : 1;
    unsigned char bit24 : 1;
    unsigned char bit25 : 1;
    unsigned char bit26 : 1;
    unsigned char bit27 : 1;
    unsigned char bit28 : 1;
    unsigned char bit29 : 1;
    unsigned char bit30 : 1;
    unsigned char bit31 : 1;
};

union bit_set
{
    uint32_t value;
    struct bits32 bits;
};

int toggle_bit(uint32_t *pvalue, int b);
int set_bit(uint32_t *pvalue, int b);
int clear_bit(uint32_t *pvalue, int b);
int isset_bit(const uint32_t *pvalue, int b);

#endif // INC_11_UNION_BIT_H
