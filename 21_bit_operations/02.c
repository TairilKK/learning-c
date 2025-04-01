#include <stdio.h>
#include <stdint.h>

int toggle_bit(uint32_t* pvalue, int b);
int set_bit(uint32_t* pvalue, int b);
int clear_bit(uint32_t* pvalue, int b);
int isset_bit(const uint32_t* pvalue, int b);

int main() {
    printf("Enter a value:\n");
    uint32_t value;
    int bit_index;
    int operation;

    if(scanf("%u", &value)!=1){
        printf("Incorrect input");
        return 1;
    }

    printf("Enter an index of a bit:\n");

    if(scanf("%d", &bit_index) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(bit_index<0 || bit_index>31){
        printf("Invalid bit index");
        return 1;
    }

    printf("Select operation (0-toggle, 1-set, 2-clear, 3-read):\n");

    if(scanf("%d", &operation) != 1){
        printf("Incorrect input");
        return 1;
    }

    if(operation == 0) { toggle_bit(&value, bit_index); printf("%08x", value); }
    else if(operation == 1) { set_bit(&value, bit_index); printf("%08x", value); }
    else if(operation == 2) { clear_bit(&value, bit_index); printf("%08x", value); }
    else if(operation == 3) { printf("%d",isset_bit(&value, bit_index)); }
    else{ printf("Invalid operation"); return 1; }


    return 0;
}

int toggle_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b<0 || b>31)
        return -1;
    *pvalue ^= 1<<b;
    return 0;
}

int set_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b<0 || b>31)
        return -1;
    *pvalue |= 1<<b;
    return 0;
}

int clear_bit(uint32_t* pvalue, int b){
    if(pvalue == NULL || b<0 || b>31)
        return -1;
    *pvalue &= ~(1<<b);
    return 0;
}

int isset_bit(const uint32_t* pvalue, int b){
    if(pvalue == NULL || b<0 || b>31)
        return -1;
    return (int)((*pvalue) & (1LL << b)) >> b;
}