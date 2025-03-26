#include <stdio.h>

int main() {
    int a;
    float b;
    char c;

    int *wa;
    float *wb;
    char *wc;

    wa=&a;
    wb=&b;
    wc=&c;

    *wa=15;
    *wb=5.64;
    *wc='&';

    printf("%d %.2f %c",*wa,*wb,*wc);

    return 0;
}
