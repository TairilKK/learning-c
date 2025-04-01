#include <stdio.h>
#include <stdint.h>

double sum(const void * const buffer, int n);

int main(void) {

    uint8_t array[] = {0x01, 0x02, 0x00, 0x03, 0x00,
                       0x00, 0x00, 0x10, 0x58, 0x39,
                       0xB4, 0xC8, 0xD6, 0x46, 0x40};

    printf("%lf", sum(array, 1));

    return 0;
}

double sum(const void * const buffer, int n){
    if (buffer == NULL || n < 1)
        return -1;

    double res = 0;
    void *array = (void *) buffer;

    for(int i = 0; i < n * 4; ++i){
        switch (i%4) {
            case 0:
                res += (double) *((uint8_t*) array);
                array = (uint8_t*) array + sizeof(uint8_t);
                break;
            case 1:
                res += (double) *((uint16_t*) array);
                array = (uint8_t*) array + sizeof(uint16_t);
                break;
            case 2:
                res += (double) *((uint32_t*) array);
                array = (uint8_t*) array + sizeof(uint32_t);
                break;
            case 3:
                res += *((double*) array);
                array = (uint8_t*) array + sizeof(double);
                break;
            default:
                break;
        }
    }

    return res;
}