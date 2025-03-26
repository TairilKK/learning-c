//
// Created by jdobr on 19.08.2023.
//

#include "09_union_bit.h"

int toggle_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b > 31 || b < 0) return -1;
    union bit_set p = {*pvalue};

    if(b == 0){if(p.bits.bit0 == 1)p.bits.bit0 = 0;else p.bits.bit0 = 1;}
    if(b == 1){if(p.bits.bit1 == 1)p.bits.bit1 = 0;else p.bits.bit1 = 1;}
    if(b == 2){if(p.bits.bit2 == 1)p.bits.bit2 = 0;else p.bits.bit2 = 1;}
    if(b == 3){if(p.bits.bit3 == 1)p.bits.bit3 = 0;else p.bits.bit3 = 1;}
    if(b == 4){if(p.bits.bit4 == 1)p.bits.bit4 = 0;else p.bits.bit4 = 1;}
    if(b == 5){if(p.bits.bit5 == 1)p.bits.bit5 = 0;else p.bits.bit5 = 1;}
    if(b == 6){if(p.bits.bit6 == 1)p.bits.bit6 = 0;else p.bits.bit6 = 1;}
    if(b == 7){if(p.bits.bit7 == 1)p.bits.bit7 = 0;else p.bits.bit7 = 1;}
    if(b == 8){if(p.bits.bit8 == 1)p.bits.bit8 = 0;else p.bits.bit8 = 1;}
    if(b == 9){if(p.bits.bit9 == 1)p.bits.bit9 = 0;else p.bits.bit9 = 1;}
    if(b == 10){if(p.bits.bit10 == 1)p.bits.bit10 = 0;else p.bits.bit10 = 1;}
    if(b == 11){if(p.bits.bit11 == 1)p.bits.bit11 = 0;else p.bits.bit11 = 1;}
    if(b == 12){if(p.bits.bit12 == 1)p.bits.bit12 = 0;else p.bits.bit12 = 1;}
    if(b == 13){if(p.bits.bit13 == 1)p.bits.bit13 = 0;else p.bits.bit13 = 1;}
    if(b == 14){if(p.bits.bit14 == 1)p.bits.bit14 = 0;else p.bits.bit14 = 1;}
    if(b == 15){if(p.bits.bit15 == 1)p.bits.bit15 = 0;else p.bits.bit15 = 1;}
    if(b == 16){if(p.bits.bit16 == 1)p.bits.bit16 = 0;else p.bits.bit16 = 1;}
    if(b == 17){if(p.bits.bit17 == 1)p.bits.bit17 = 0;else p.bits.bit17 = 1;}
    if(b == 18){if(p.bits.bit18 == 1)p.bits.bit18 = 0;else p.bits.bit18 = 1;}
    if(b == 19){if(p.bits.bit19 == 1)p.bits.bit19 = 0;else p.bits.bit19 = 1;}
    if(b == 20){if(p.bits.bit20 == 1)p.bits.bit20 = 0;else p.bits.bit20 = 1;}
    if(b == 21){if(p.bits.bit21 == 1)p.bits.bit21 = 0;else p.bits.bit21 = 1;}
    if(b == 22){if(p.bits.bit22 == 1)p.bits.bit22 = 0;else p.bits.bit22 = 1;}
    if(b == 23){if(p.bits.bit23 == 1)p.bits.bit23 = 0;else p.bits.bit23 = 1;}
    if(b == 24){if(p.bits.bit24 == 1)p.bits.bit24 = 0;else p.bits.bit24 = 1;}
    if(b == 25){if(p.bits.bit25 == 1)p.bits.bit25 = 0;else p.bits.bit25 = 1;}
    if(b == 26){if(p.bits.bit26 == 1)p.bits.bit26 = 0;else p.bits.bit26 = 1;}
    if(b == 27){if(p.bits.bit27 == 1)p.bits.bit27 = 0;else p.bits.bit27 = 1;}
    if(b == 28){if(p.bits.bit28 == 1)p.bits.bit28 = 0;else p.bits.bit28 = 1;}
    if(b == 29){if(p.bits.bit29 == 1)p.bits.bit29 = 0;else p.bits.bit29 = 1;}
    if(b == 30){if(p.bits.bit30 == 1)p.bits.bit30 = 0;else p.bits.bit30 = 1;}
    if(b == 31){if(p.bits.bit31 == 1)p.bits.bit31 = 0;else p.bits.bit31 = 1;}
    *pvalue = p.value;
    return 0;
}

int set_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b > 31 || b < 0) return -1;
    union bit_set p = {*pvalue};

    if(b == 0)p.bits.bit0 = 1;
    if(b == 1)p.bits.bit1 = 1;
    if(b == 2)p.bits.bit2 = 1;
    if(b == 3)p.bits.bit3 = 1;
    if(b == 4)p.bits.bit4 = 1;
    if(b == 5)p.bits.bit5 = 1;
    if(b == 6)p.bits.bit6 = 1;
    if(b == 7)p.bits.bit7 = 1;
    if(b == 8)p.bits.bit8 = 1;
    if(b == 9)p.bits.bit9 = 1;
    if(b == 10)p.bits.bit10 = 1;
    if(b == 11)p.bits.bit11 = 1;
    if(b == 12)p.bits.bit12 = 1;
    if(b == 13)p.bits.bit13 = 1;
    if(b == 14)p.bits.bit14 = 1;
    if(b == 15)p.bits.bit15 = 1;
    if(b == 16)p.bits.bit16 = 1;
    if(b == 17)p.bits.bit17 = 1;
    if(b == 18)p.bits.bit18 = 1;
    if(b == 19)p.bits.bit19 = 1;
    if(b == 20)p.bits.bit20 = 1;
    if(b == 21)p.bits.bit21 = 1;
    if(b == 22)p.bits.bit22 = 1;
    if(b == 23)p.bits.bit23 = 1;
    if(b == 24)p.bits.bit24 = 1;
    if(b == 25)p.bits.bit25 = 1;
    if(b == 26)p.bits.bit26 = 1;
    if(b == 27)p.bits.bit27 = 1;
    if(b == 28)p.bits.bit28 = 1;
    if(b == 29)p.bits.bit29 = 1;
    if(b == 30)p.bits.bit30 = 1;
    if(b == 31)p.bits.bit31 = 1;

    *pvalue = p.value;
    return 0;

}
int clear_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b > 31 || b < 0) return -1;
    union bit_set p = {*pvalue};

    if(b == 0)p.bits.bit0 = 0;
    if(b == 1)p.bits.bit1 = 0;
    if(b == 2)p.bits.bit2 = 0;
    if(b == 3)p.bits.bit3 = 0;
    if(b == 4)p.bits.bit4 = 0;
    if(b == 5)p.bits.bit5 = 0;
    if(b == 6)p.bits.bit6 = 0;
    if(b == 7)p.bits.bit7 = 0;
    if(b == 8)p.bits.bit8 = 0;
    if(b == 9)p.bits.bit9 = 0;
    if(b == 10)p.bits.bit10 = 0;
    if(b == 11)p.bits.bit11 = 0;
    if(b == 12)p.bits.bit12 = 0;
    if(b == 13)p.bits.bit13 = 0;
    if(b == 14)p.bits.bit14 = 0;
    if(b == 15)p.bits.bit15 = 0;
    if(b == 16)p.bits.bit16 = 0;
    if(b == 17)p.bits.bit17 = 0;
    if(b == 18)p.bits.bit18 = 0;
    if(b == 19)p.bits.bit19 = 0;
    if(b == 20)p.bits.bit20 = 0;
    if(b == 21)p.bits.bit21 = 0;
    if(b == 22)p.bits.bit22 = 0;
    if(b == 23)p.bits.bit23 = 0;
    if(b == 24)p.bits.bit24 = 0;
    if(b == 25)p.bits.bit25 = 0;
    if(b == 26)p.bits.bit26 = 0;
    if(b == 27)p.bits.bit27 = 0;
    if(b == 28)p.bits.bit28 = 0;
    if(b == 29)p.bits.bit29 = 0;
    if(b == 30)p.bits.bit30 = 0;
    if(b == 31)p.bits.bit31 = 0;
    *pvalue = p.value;
    return 0;
}
int isset_bit(const uint32_t* pvalue, int b){
    if(pvalue == NULL) return -1;
    union bit_set p = {*pvalue};

    if(b == 0)return (int) p.bits.bit0;
    if(b == 1)return (int) p.bits.bit1;
    if(b == 2)return (int) p.bits.bit2;
    if(b == 3)return (int) p.bits.bit3;
    if(b == 4)return (int) p.bits.bit4;
    if(b == 5)return (int) p.bits.bit5;
    if(b == 6)return (int) p.bits.bit6;
    if(b == 7)return (int) p.bits.bit7;
    if(b == 8)return (int) p.bits.bit8;
    if(b == 9)return (int) p.bits.bit9;
    if(b == 10)return (int) p.bits.bit10;
    if(b == 11)return (int) p.bits.bit11;
    if(b == 12)return (int) p.bits.bit12;
    if(b == 13)return (int) p.bits.bit13;
    if(b == 14)return (int) p.bits.bit14;
    if(b == 15)return (int) p.bits.bit15;
    if(b == 16)return (int) p.bits.bit16;
    if(b == 17)return (int) p.bits.bit17;
    if(b == 18)return (int) p.bits.bit18;
    if(b == 19)return (int) p.bits.bit19;
    if(b == 20)return (int) p.bits.bit20;
    if(b == 21)return (int) p.bits.bit21;
    if(b == 22)return (int) p.bits.bit22;
    if(b == 23)return (int) p.bits.bit23;
    if(b == 24)return (int) p.bits.bit24;
    if(b == 25)return (int) p.bits.bit25;
    if(b == 26)return (int) p.bits.bit26;
    if(b == 27)return (int) p.bits.bit27;
    if(b == 28)return (int) p.bits.bit28;
    if(b == 29)return (int) p.bits.bit29;
    if(b == 30)return (int) p.bits.bit30;
    if(b == 31)return (int) p.bits.bit31;
    return -1;
}
