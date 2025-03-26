#include <stdio.h>

long int fibonacci(int n);

int main()
{
    int n;
    
    printf("KtĂłry wyraz ciagu fibonacciego chcesz wyznaczyÄ: ");
    if(scanf("%d", &n)!=1){
        printf("incorrect input");
        return 1;
    }
    if(fibonacci(n)==-1){
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %ld",fibonacci(n));
    return 0;
}
long int fibonacci(int n){
    if(n<0)
        return -1;
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}
