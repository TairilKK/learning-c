#include <stdio.h>

int main() {
    int a,*b;

    a=1;
    b=&a;

    printf("%d %d %p\n",a,*b,(void *)b);

    *b=5;
    printf("%d %d %p",a,*b,(void *)b);

    return 0;
}
