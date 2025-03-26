#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand (time(NULL));
    int T[20];


    for(int* p=T; p<T+20; p++)
        *p=rand()%21;

    for(int* p=T; p<T+20; p++)
        printf("%d ",*p);

    printf("\n");

    for(int* p=T; p<T+20; p+=2)
        printf("%d ",*p);

    return 0;
}
