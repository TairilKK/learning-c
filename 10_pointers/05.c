#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand (time(NULL));
    float T[20];


    for(float* p=T; p<T+20; p++)
        *p=(float)rand()/RAND_MAX;

    for(float* p=T; p<T+20; p++)
        printf("%.2f ",*p);

    printf("\n");

    for(float* p=T; p<T+20; p+=2)
        printf("%.2f ",*p);

    return 0;
}
