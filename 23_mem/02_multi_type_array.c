#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define READ_TYPES(type) \
for(uint8_t j = 0; j<len; ++j){\
*result += (double) *((type *) array); \
array=(uint8_t *)array+sizeof(type);                         \
}


void* sum(const void * const ptr, int size);

int main(void) {
    uint8_t test1[] = {0x13, 0x01, 0x02, 0x03};
    double *res1 = sum((const void*)test1, 1);
    printf("%lf\n", *res1);
    free(res1);

    uint8_t test2[] = {0x13, 0x01, 0x02, 0x03,0x24,
                       0x00, 0x01, 0x00, 0x00,
                       0x00, 0x02, 0x00, 0x00,
                       0x00, 0x03, 0x00, 0x00,
                       0x00, 0x04, 0x00, 0x00};
    double *res2 = sum((const void*)test2, 2);
    printf("%lf", *res2);
    free(res2);
    return 0;
}

void* sum(const void * const ptr, int size){
    if(ptr == NULL || size < 1)
        return NULL;

    void * array = (void*) ptr;
    double *result = (double*)calloc(1, sizeof(double));

    for(int i = 0; i<size; ++i){

        uint8_t byte = *((uint8_t*) array);
        array = (uint8_t *)array+1;
        uint8_t type = (byte & (0xF0))>>4;
        uint8_t len = byte & (0x0F);

        switch (type){
            case 0:
                READ_TYPES(char)
                break;
            case 1:
                READ_TYPES(unsigned char)
                break;
            case 2:
                READ_TYPES(int32_t)
                break;
            case 3:
                READ_TYPES(uint32_t)
                break;
            case 4:
                READ_TYPES(float)
                break;
            case 5:
                READ_TYPES(double)
                break;
            default:
                free(result);
                return NULL;
        }
    }

    return result;
}