#include <stdio.h>

int main() {

    int T[10];

    for(int* p=T; p<T+10; p++)
        *p=p-T;
    for(int* p=T; p<T+10; p++)
        printf("%d ",*p);

    return 0;
}
