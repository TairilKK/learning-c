#include <stdio.h>

int sum_short_int_int(const void * const in1, const void * const in2, void *out);

int main(void) {
    const short a = 4;
    const int b = 15;
    int out = 0;
    printf("%d %d %d\n", a, b, out);
    int res = sum_short_int_int((const void*)&a, (const void*)&b, (void*)&out );
    printf("%d %d %d\n", a, b, out);
    printf("%d", res);
    return 0;
}

int sum_short_int_int(const void * const in1, const void * const in2, void *out){
    if(in1 == NULL || in2 == NULL || out == NULL) {
        return 1;
    }

    short* a = (short *) in1;
    int *b = (int*) in2, *res = (int*) out;
    *res = *a + *b;

    return 0;
}
