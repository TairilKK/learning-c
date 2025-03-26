#include <stdio.h>

#include "09_union_bit.h"

int main() {
    uint32_t input_value;
    int index, operation;
    printf("Enter a value: \n");
    if(scanf("%u", &input_value)!=1){
        printf("Incorrect input");
        return 1;
    }

    printf("Enter an index of a bit:\n");
    if(scanf("%d", &index)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(index<0 || index>31){
        printf("Invalid bit index");
        return 2;
    }

    printf("Select operation (0-toggle, 1-set, 2-clear, 3-read):\n");
    if(scanf("%d", &operation)!=1){
        printf("Incorrect input");
        return 1;
    }

    switch (operation) {
        case 0:
            toggle_bit(&input_value, index);
            printf("%x", input_value);
            break;
        case 1:
            set_bit(&input_value, index);
            printf("%x", input_value);
            break;
        case 2:
            clear_bit(&input_value, index);
            printf("%x", input_value);
            break;
        case 3:
            printf("%d",isset_bit(&input_value, index));
            break;
        default:
            printf("Invalid operation");
            return 2;
    }
    return 0;
}

