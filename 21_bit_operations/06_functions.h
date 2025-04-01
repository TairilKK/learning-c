//
// Created by jdobr on 24.07.2023.
//

#ifndef INC_13_FUNCTIONS_H
#define INC_13_FUNCTIONS_H

#define DISPLAY_BITS(value) \
do{                        \
    for(int i = sizeof(value) * 8 - 1; i >= 0; --i) \
        printf("%d", ((value) & (1ULL << i) ? 1 : 0));    \
    printf("\n");\
}while(0)

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) \
do{\
    *(pointer_to_bits_set_counter) = 0;                                                   \
    *(pointer_to_bits_cleared_counter) = 0;                                               \
    for(int i = sizeof(value) * 8 - 1; i >= 0; --i){\
        if((value) & (1ULL << i))\
            *(pointer_to_bits_set_counter) += 1;                                             \
        else                                                                            \
            *(pointer_to_bits_cleared_counter) += 1;\
    }                                                                                   \
}while(0)

#define REVERSE_BITS(pointer_to_variable) \
do {                                      \
    unsigned long long temp = 0;          \
    int size = sizeof(*(pointer_to_variable)) * 8 - 1; \
    for (int i = size; i >= 0; --i)       \
        if (*(pointer_to_variable) & (1ULL << i)) \
            temp |= 1ULL << (size - i);   \
    *(pointer_to_variable) = temp;        \
} while (0)



#endif //INC_13_FUNCTIONS_H
