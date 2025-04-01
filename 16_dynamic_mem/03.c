#include <stdio.h>
#include <stdlib.h>

float* create_array(int N);

int main( )
{
    int n;
    printf("Podaj ilosc elementow:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(n<1){
        printf("Incorrect input data");
        return 2;
    }
    float *p= create_array(n);
    if(p==NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby:\n");
    for(int i=0;i<n;i++){
        if(scanf("%f",(p+i))!=1){
            printf("incorrect input");
            free(p);
            return 1;
        }
    }
    for(int i=n-1;i>=0;i--)
        printf("%f ",*(p+i));

    free(p);

    return 0;
}
float* create_array(int N){
    if(N<1)
        return NULL;
    return (float*) malloc(N*sizeof(float ));
}
