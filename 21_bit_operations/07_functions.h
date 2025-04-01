//
// Created by jdobr on 09.08.2023.
//

#ifndef INC_14_FUNCTIONS_H
#define INC_14_FUNCTIONS_H

#define CREATE_READ_FUNCTIONS(TYPE, FORMAT) \
int read_##TYPE(TYPE *data, int size){      \
    if(data == NULL || size < 1) return 1;\
    printf("Podaj liczby:");                                        \
    for(int i = 0; i < size; ++i)          \
        if(scanf(FORMAT, (data + i))!= 1)                   \
            return 2;                       \
    return 0;\
}

#define CREATE_SORT_FUNCTIONS(TYPE) \
int sort_##TYPE(TYPE *data, int size){\
    if(data == NULL || size < 1) return 1;      \
    TYPE temp;\
    for(int i = 0; i < size - 1; ++i)   \
        for(int j = 0; j < size - 1 - i; ++j) \
             if(*(data + j) > *(data + j + 1)){ \
                temp = *(data + j); \
                *(data + j) = *(data + j + 1);\
                *(data + j + 1) = temp;\
             }                           \
    return 0;                                    \
}


#define CREATE_DISPLAY_FUNCTIONS(TYPE, FORMAT) \
void display_##TYPE(const TYPE *data, int size){ \
    if(data == NULL || size < 1) return;                   \
    for(int i = 0; i < size; printf(FORMAT" " ,*(data + i)), ++i);\
}

#endif //INC_14_FUNCTIONS_H
